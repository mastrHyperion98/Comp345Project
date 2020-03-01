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
using namespace std;
using namespace boost;


VGMap::VGMap() {
    CreateVillageField();
}
// Define the deconstructor of the GameBoard Map
VGMap::~VGMap() = default;
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
        (*village_board)[vPosition].setPosition(vPosition);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (vPosition > 0 && vPosition % 5 != 0)
            add_edge(vPosition, vPosition - 1, *village_board);


        if (vPosition>=0 && vPosition<5) {
            (*village_board)[vPosition].setVCost(6);
            (*village_board)[vPosition].setRow(0);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }

        else if (vPosition>=5 && vPosition<10) {
            (*village_board)[vPosition].setVCost(5);
            (*village_board)[vPosition].setRow(1);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }

        else if (vPosition>=10 && vPosition<15) {
            (*village_board)[vPosition].setVCost(4);
            (*village_board)[vPosition].setRow(2);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }

        else if (vPosition>=15 && vPosition<20) {
            (*village_board)[vPosition].setVCost(3);
            (*village_board)[vPosition].setRow(3);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }
        else if (vPosition>=20 && vPosition<25) {
            (*village_board)[vPosition].setVCost(2);
            (*village_board)[vPosition].setRow(4);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }

        else if (vPosition>=25 && vPosition<30) {
            (*village_board)[vPosition].setVCost(1);
            (*village_board)[vPosition].setRow(5);
            (*village_board)[vPosition].setCol(vPosition % 5);
        }
    }

    for (int vPosition = 0; vPosition < 25; vPosition++) {
        add_edge(vPosition, vPosition + 5, *village_board);
    }

}
void VGMap::PrintGraph() {
    boost::print_graph(*village_board);
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
            if ((*board)[next_element].getColumn() == column && !*(*board)[next_element].isVisited) {
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
            if ((*board)[next_element].getRow() == row && !*(*board)[next_element].isVisited) {
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

Circle VGMap::getCircle(int position) {
    if(position < 30 && position >= 0)
       return (*village_board)[position];
    else
        throw 2;
}

void VGMap::resetVisited() {
    for(int i = 0; i < 30; i++){
         *(*village_board)[i].isVisited = false;
    }
}

void VGMap::setBuilding(int position, Building *building) {
    (*village_board)[position].setBuilding(building);
}
Circle::Circle(){

}

Circle::Circle(const Circle &circle){
    if(circle.building != nullptr){
        building = new Building(*circle.building);
    } else
        building = nullptr;
    row = new int(*circle.row);
    column = new int(*circle.column);
    vCost = new int(*circle.vCost);
    isVisited = new bool(*circle.isVisited);
    isPlayed = new bool(*circle.isPlayed);
}

Circle::~Circle() {
    delete building;
    delete row;
    delete column;
    delete vCost;
    delete isVisited;
    delete isPlayed;
}
int Circle::getRow() const{
    return *row;
}

int Circle::getColumn() const{
    return *column;
}

int Circle::getPosition() const{
    return *position;
}

int Circle::getVCost() const{
    return *vCost;
}

Building* Circle::getBuilding() const{
    return building;
}

void Circle::setCol(int col) {
    column = new int(col);
}

void Circle::setRow(int row) {
    this->row = new int(row);
}

void Circle::setVCost(int cost) {
    vCost = new int(cost);
}

void Circle::setBuilding(Building * building) {
    if(!*isPlayed) {
        this->building = building;
        *this->isPlayed = true;
        return;
    }
    throw 1;
}

void Circle::setPosition(int pos) {
    position = new int(pos);
}
bool Circle::getIsPlayed() const {
    return *isPlayed;
}