//
// Created by Nizz Wizz on 2020-02-05.
//

#include "VGMap.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/connected_components.hpp"
// include the io stream library
#include <iostream>
// include the string library
#include <string>
#include <deque>
#include <iomanip>

using namespace std;
using namespace boost;


VGMap::VGMap(string v_name): typePlayed(new map<ResourceTypes, bool>), name{new string(v_name)},village_board{new C_Graph}{
    CreateVillageField();
    typePlayed->insert(pair<ResourceTypes, bool>(ResourceTypes::WHEAT, false));
    typePlayed->insert(pair<ResourceTypes, bool>(ResourceTypes::STONE, false));
    typePlayed->insert(pair<ResourceTypes, bool>(ResourceTypes::SHEEP, false));
    typePlayed->insert(pair<ResourceTypes, bool>(ResourceTypes::WOOD, false));
}
// Define the deconstructor of the GameBoard Map
VGMap::~VGMap() {
    delete village_board;
    delete name;
}

VGMap::VGMap(const VGMap &map) {
    if(map.village_board !=nullptr)
    village_board = new C_Graph(*map.village_board);
    typePlayed = new  std::map<ResourceTypes, bool>(*map.typePlayed);
    // here we can use operator overload
    if(map.name!=nullptr)
    name = new string(*map.name);
    else
        name = nullptr;
}

VGMap & VGMap::operator=(const VGMap &map){
    if(this == &map)
        return *this;
    else{
        delete village_board;
        *village_board = *map.village_board;
        *typePlayed = *map.typePlayed;
        *name = *map.name;
    }

    return *this;
}
// Function that goes and fetches the graph
// generate the graph
/*
The gameboard will be initiated in parts, based on the configuration of the board (aka # of players)
Each vertex (Square) will be labeled with a number. That number will be indentical to its index in the graph
and will start at 0 at the upper left most corner of the 2 player field. From there, the vertices will be created row by row.
It will be created in a similar way as a 2D Matrix.
*/
// create the center 5x5 field area
void VGMap::CreateVillageField() {
    for (int vPosition = 0; vPosition < 30; vPosition++) {
        add_vertex(*village_board);
        (*village_board)[vPosition].position = new int(vPosition);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (vPosition > 0 && vPosition % 5 != 0)
            add_edge(vPosition, vPosition - 1, *village_board);


        if (vPosition>=0 && vPosition<5) {
            (*village_board)[vPosition].vCost = new int(6);
            (*village_board)[vPosition].row = new int(0);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        else if (vPosition>=5 && vPosition<10) {
            (*village_board)[vPosition].vCost = new int(5);
            (*village_board)[vPosition].row = new int(1);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        else if (vPosition>=10 && vPosition<15) {
            (*village_board)[vPosition].vCost = new int(4);
            (*village_board)[vPosition].row = new int(2);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        else if (vPosition>=15 && vPosition<20) {
            (*village_board)[vPosition].vCost = new int(3);
            (*village_board)[vPosition].row = new int(3);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }
        else if (vPosition>=20 && vPosition<25) {
            (*village_board)[vPosition].vCost = new int(2);
            (*village_board)[vPosition].row = new int(4);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        else if (vPosition>=25 && vPosition<30) {
            (*village_board)[vPosition].vCost = new int(1);
            (*village_board)[vPosition].row = new int(5);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }
    }

    for (int vPosition = 0; vPosition < 25; vPosition++) {
        add_edge(vPosition, vPosition + 5, *village_board);
    }

}
void VGMap::PrintGraph() {
    // here we are going to print the graph
    // content of row | row value
    // column value|
    const string spacer = "    ";
    const string inner_spacer ="  ";
    cout << spacer << spacer << spacer << spacer << spacer << "***" << *name << "***" << spacer << spacer << endl;
    cout << "------------" << "-------------------------------------------------------------" << endl;
    int num_row{0};
    for(int i{0}; i < 6; i++){
        std::cout << spacer << spacer <<  (6 - i) << " |" << spacer;
        for(int j{5*i}; j < 5*i + 5; j++){
            if((*village_board)[j].building == nullptr){
                cout << std::setfill('0') << std::setw(2)<<*(*village_board)[j].position << spacer;
            }else{
                cout << castResourceTypesToString((*village_board)[j].building->getBuildingType()) << spacer;
            }
        }
        switch(num_row){
            case 0: cout << spacer << " | #Colonists: " <<  std::setfill('0') << std::setw(2)<<6; break;
            case 1: cout << spacer << " | #Colonists: " << std::setfill('0') << std::setw(2)<<5; break;
            case 2: cout << spacer << " | #Colonists: " << std::setfill('0') << std::setw(2)<<4; break;
            case 3: cout << spacer << " | #Colonists: " << std::setfill('0') << std::setw(2)<<3; break;
            case 4: cout << spacer << " | #Colonists: " << std::setfill('0') << std::setw(2)<<2; break;
            case 5: cout << spacer << " | #Colonists: " << std::setfill('0') << std::setw(2)<<1; break;
        }
        num_row++;
        cout << endl;
    }
    cout << "------------" << "-------------------------------------------------------------" << endl;
    cout << "#Colonists|  " << inner_spacer;
    cout << std::setfill('0') << std::setw(2)<< 5<< spacer;
    cout << std::setfill('0') << std::setw(2)<< 4 << spacer;
    cout << std::setfill('0') << std::setw(2)<< 3 << spacer;
    cout << std::setfill('0') << std::setw(2)<< 4 << spacer;
    cout << std::setfill('0') << std::setw(2)<< 5 << spacer;

    cout << endl << endl;

}
// Taken from the Boost Connected Graph Example
//https://www.boost.org/doc/libs/1_65_0/libs/graph/example/connected_components.cpp
// Prints the number of Connected Components and which vertex belongs to which component
// A component is a set of one or more nodes in which a path exists.
// In other words, if the graph is connected than there is only 1 component.
// If component 2 exists then there does not exists a path linking nodes from Component 1 and 2.
void VGMap::PrintConnectedGraph() {

    std::vector<int> component(num_vertices(*village_board));
    int num = connected_components(*village_board, &component[0]);

    std::vector<int>::size_type i;
    cout << "Total number of components: " << num << endl;
    for (i = 0; i != component.size(); ++i)
        cout << "Circle " << i <<" is in component " << component[i] << endl;
    cout << endl;
}

// returns a graph with all the connected nodes in the selected column
// same logic as getConnectedRow
ConnectedCircles VGMap::getConnectedColumn(int const column){
    C_Graph *board = new C_Graph(*village_board);
    ConnectedCircles graph;
    deque<vertex_v> root_queue;
    int origin_index = column % 5;
    auto vertex_set = board->vertex_set();
    vertex_v vertex = vertex_set[origin_index];
    vertex_v origin_v = add_vertex(graph);
    graph[origin_v] = Circle((*board)[vertex]);
    root_queue.push_back(vertex);

    while (!root_queue.empty()) {
        vertex = root_queue.front();
        *(*board)[vertex].isVisited = true;
        C_Graph::adjacency_iterator start, end;
        tie(start, end) = adjacent_vertices(vertex, *board);
        for (; start != end; ++start) {
            // create the next element
            vertex_v next_element = vertex_set[*start];
            if (*(*board)[next_element].column == column && !*(*board)[next_element].isVisited) {
                // if the next_element is in the same column then push to queue
                root_queue.push_back(next_element);
                // add a vertex to the connectedCircles graph
                vertex_v v = add_vertex(graph);
                // assign circle to the next element of the graph
                graph[v] = Circle((*board)[next_element]);
                // add an edge -- origin_v always in front
                add_edge(origin_v, v, graph);
                // before leaving set v as the new origin;
                origin_v = v;
                // break
                break;
            }
        }
        // remove the front of the queue when the for loop is over.
        root_queue.pop_front();
    }
    resetVisited();
// return the new graph
    delete board;
    return graph;
}

// returns a graph with all the connected nodes in the selected row
ConnectedCircles VGMap::getConnectedRow(int const row) {
    C_Graph *board = new C_Graph(*village_board);
    ConnectedCircles graph;
    // create a queue to keep track of the next element to traverse
    deque<vertex_v> root_queue;
    int origin_index = 5 * row;
    // define the vertexSet of Village Board
    auto vertex_set = board->vertex_set();
    // get vertex from village board
    vertex_v vertex = vertex_set[origin_index];
    // create new vertex in ConnectedGraph graph
    vertex_v origin_v = add_vertex(graph);


    // assign the circle from vertex to origin_v
    graph[origin_v] = Circle((*board)[vertex]);
    // push origin into queue
    root_queue.push_back(vertex);


    // while queue is not empty iterate
    while (!root_queue.empty()) {
        // get the head of the queue
        vertex = root_queue.front();
        *(*board)[vertex].isVisited = true;
        // define your adjacency iterator
        C_Graph::adjacency_iterator start, end;
        tie(start, end) = adjacent_vertices(vertex, *board);
        for (; start != end; ++start) {
            // create the next element
            vertex_v next_element = vertex_set[*start];
            if (*(*board)[next_element].row == row && !*(*board)[next_element].isVisited) {
                // if the next_element is in the same row then push to queue
                root_queue.push_back(next_element);
                // add a vertex to the connectedCircles graph
                vertex_v v = add_vertex(graph);
                // assign circle to the next element of the graph
                graph[v] = Circle((*board)[next_element]);
                // add an edge -- origin_v always in front
                add_edge(origin_v, v, graph);
                // before leaving set v as the new origin;
                origin_v = v;
                // break
                break;
            }
        }
        // remove the front of the queue when the for loop is over.
        root_queue.pop_front();
    }
    delete board;
    resetVisited();
// return the new graph
    return graph;
}

bool VGMap::isPlayed(int position) {
    if(position < 30 && position >= 0)
       return *(*village_board)[position].isPlayed;
    else
        return false;
}

void VGMap::resetVisited() {
    for(int i = 0; i < 30; i++){
         *(*village_board)[i].isVisited = false;
    }
}
bool VGMap::setBuilding(int position, Building *building) {
    if(building->getBuildingNumber() == *(*village_board)[position].vCost && !building->isFlipped()){
        if( building->getBuildingType() == ResourceTypes::WOOD && ! (*typePlayed)[ResourceTypes::WOOD]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::WOOD] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::WOOD &&  (*typePlayed)[ResourceTypes::WOOD]){
            // check adjacency
            if(isAdjacentType(ResourceTypes::WOOD, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }
        }
        else if( building->getBuildingType() == ResourceTypes::STONE && ! (*typePlayed)[ResourceTypes::STONE]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::STONE] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::STONE &&  (*typePlayed)[ResourceTypes::STONE]){
            if(isAdjacentType(ResourceTypes::STONE, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }

        }
        else if( building->getBuildingType() == ResourceTypes::SHEEP && ! (*typePlayed)[ResourceTypes::SHEEP]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::SHEEP] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::SHEEP &&  (*typePlayed)[ResourceTypes::SHEEP]){
            if(isAdjacentType(ResourceTypes::SHEEP, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }

        }
        else if( building->getBuildingType() == ResourceTypes::WHEAT && ! (*typePlayed)[ResourceTypes::WHEAT]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::WHEAT] = true;

            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::WHEAT &&  (*typePlayed)[ResourceTypes::WHEAT]){
            if(isAdjacentType(ResourceTypes::WHEAT, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }
        }
    }
    else if(building->isFlipped()){
        if( building->getBuildingType() == ResourceTypes::WOOD && ! (*typePlayed)[ResourceTypes::WOOD]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::WOOD] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::WOOD &&  (*typePlayed)[ResourceTypes::WOOD]){
            // check adjacency
            if(isAdjacentType(ResourceTypes::WOOD, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }
        }
        else if( building->getBuildingType() == ResourceTypes::STONE && ! (*typePlayed)[ResourceTypes::STONE]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::STONE] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::STONE &&  (*typePlayed)[ResourceTypes::STONE]){
            if(isAdjacentType(ResourceTypes::STONE, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }

        }
        else if( building->getBuildingType() == ResourceTypes::SHEEP && ! (*typePlayed)[ResourceTypes::SHEEP]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::SHEEP] = true;
            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::SHEEP &&  (*typePlayed)[ResourceTypes::SHEEP]){
            if(isAdjacentType(ResourceTypes::SHEEP, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }

        }
        else if( building->getBuildingType() == ResourceTypes::WHEAT && ! (*typePlayed)[ResourceTypes::WHEAT]){
            (*village_board)[position].building = building;
            *(*village_board)[position].isPlayed = true;
            (*typePlayed)[ResourceTypes::WHEAT] = true;

            return true;
        }
        else if(building->getBuildingType() == ResourceTypes::WHEAT &&  (*typePlayed)[ResourceTypes::WHEAT]){
            if(isAdjacentType(ResourceTypes::WHEAT, position)){
                (*village_board)[position].building = building;
                *(*village_board)[position].isPlayed = true;
                return true;
            }
        }
    }
    return false;
}


bool VGMap::isAdjacentType(ResourceTypes type, int position) {
    // can only be called internally no need to verify the bounds of position
    vertex_v root = village_board->vertex_set()[position];
    C_Graph::adjacency_iterator start, end;
    tie(start, end) = adjacent_vertices(root, *village_board);
    for (; start != end; ++start) {
        // create the next element
        if((*village_board)[*start].building != nullptr && type == (*village_board)[*start].building->getBuildingType())
            return true;
        }
    return false;
}
Circle::Circle(){
    row = nullptr;
    column = nullptr;
    vCost = nullptr;
    building = nullptr;
    position = nullptr;
    isVisited = new bool(false);
    isPlayed = new bool(false);
}

Circle::Circle(const Circle &circle){
    building = circle.building;
    row = new int(*circle.row);
    position = new int(*circle.position);
    column = new int(*circle.column);
    vCost = new int(*circle.vCost);
    isVisited = new bool(*circle.isVisited);
    isPlayed = new bool(*circle.isPlayed);
}

Circle::~Circle(){
    delete row;
    delete column;
    delete vCost;
    delete isVisited;
    delete position;
    delete isPlayed;
}

// override assignment operator
Circle & Circle::operator=(const Circle &circle){
    if (this == &circle)
        return *this;
    else {
        row = new int(*circle.row);
        column = new int(*circle.column);
        vCost = new int(*circle.vCost);
        *isVisited = *circle.isVisited;
        *isPlayed = *circle.isPlayed;
        // we dont create copies of buildings. We will clear it with the decks
        building = circle.building;
        position = new int(*circle.position);
    }
    return *this;
}

int VGMap::getPositionCost(int position){
    if(position >= 0 && position < 30)
        return *(*village_board)[position].vCost;
    return -1;
}

string VGMap::getName(){
    return *name;
}


string VGMap::castResourceTypesToString(ResourceTypes type){
    if(type == ResourceTypes::SHEEP)
        return "SH";
    else if(type == ResourceTypes::WOOD)
        return "WD";
    else if(type == ResourceTypes::STONE)
        return "ST";
    else if(type == ResourceTypes::WHEAT)
        return "WT";
}

int VGMap::getNumUnplayed(){
    // essentially we loop through
    int num_empty{0};

    for(int i = 0; i < 30; i++)
        if (!*(*village_board)[i].isPlayed) {
            if ((*village_board)[i].building == nullptr)
                num_empty++;
        }

    return num_empty;
}