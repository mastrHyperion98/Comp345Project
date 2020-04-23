/*This file contains the functions and properties used by the New Haven Game Map.
 * The map is a connected graph implemented using the boost graph library.
 * Created by Steven on 2020-01-31.
 * Created for Concordia W 2020 Comp 345 New Haven Project
 */

// include boost adjacency_list
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/copy.hpp"
#include "../src/GBMap.h"
#include <iomanip>

GBMap::GBMap(int configuration):CONFIG(new const int(configuration)), SIZE(new const int(25 + (*CONFIG*10))), buildings{new std::vector<Building*>},
last_played{nullptr}{
    board = new GameBoard();
    // populate board
    if(!createBoard())
        // create a proper exception maybe
        throw 1;
    // assign
    assignDefaultTiles();
}
GBMap::GBMap(const GBMap &map) : CONFIG(new const int(*map.CONFIG)), SIZE(new const int(25 + (*map.CONFIG*10))), buildings{new std::vector<Building*>(*map.buildings)},
last_played{nullptr}{
    // call the copy constructor of the GameBoard
    board = new GameBoard(*map.board);
    *playCounter = *map.playCounter;

    if(map.last_played!=nullptr)
        last_played = new Square(*map.last_played);
}
GBMap::~GBMap(){
    delete CONFIG;
    delete SIZE;
    delete board;
    delete buildings;
    delete tl;
    delete tr;
    delete bl;
    delete br;
    delete playCounter;
    delete last_played;
    // set to nullptr since it is static and belongs to the class.
}
GBMap::GBMap():CONFIG(new const int(0)), SIZE(new const int(25)),buildings{new std::vector<Building*>}{
    board = new GameBoard();
    // populate board
    if(!createBoard())
        // create a proper exception maybe
        throw 1;
}
bool GBMap::placeHarvestTile(int NodeID, HarvestTile *tile) {
 if(NodeID > *SIZE || NodeID < 0|| &tile == nullptr ||*(*board)[NodeID].isPlayed )
     return false;
    // should use the operator overload
    (*board)[NodeID].tile = tile;
    *(*board)[NodeID].isPlayed = true;
    *playCounter = *playCounter + 1;
    delete last_played;
    last_played = new Square((*board)[NodeID]);
    notify();
    return true;
}
ResourceTrails * GBMap::getResourcedGraph(int position) {
    // create a copy of the game_board
    // and use the copy throughout
    ResourceTrails* connectedGraph{ new ResourceTrails };
    auto vertices{ (*board).vertex_set() };
    NodeID first_v{ vertices[position] };
    NodeID root{ add_vertex(*connectedGraph) };
    // copy the squares! IMPORTANT!
    (*connectedGraph)[root] = (*board)[first_v];
    deque<NodeID> queue;
    deque<NodeID> root_queue;
    queue.push_back(first_v);
    root_queue.push_back(root);

    while(!queue.empty()) {
        GameBoard::adjacency_iterator neighbourIt, neighbourEnd;
        // origin of the current search
        NodeID origin{ queue.front() };
        root = root_queue.front();

        for (tie(neighbourIt, neighbourEnd) = adjacent_vertices(origin, *board); neighbourIt != neighbourEnd; ++neighbourIt) {
            *(*board)[origin].isVisited = true;
            // next_element
            NodeID next_element{ vertices[*neighbourIt] };
            // if the element has not been visited yet and is a playedTile add to the new graph and add to queue to
            // search its neighbours
           if(*(*board)[next_element].isVisited && *(*board)[next_element].isPlayed){
               int v_position{ getVertexPosition(*connectedGraph, *(*board)[next_element].position) };
                add_edge(root, (*connectedGraph).vertex_set()[v_position], *connectedGraph);
            }
           else if (!*(*board)[next_element].isVisited && *(*board)[next_element].isPlayed){
                if( !vertexContainedInQueue(queue, next_element))
                    queue.push_back(next_element);

                if(getVertexPosition(*connectedGraph, *(*board)[next_element].position) < 0){
                    NodeID vertex1{ add_vertex(*connectedGraph) };
                    (*connectedGraph)[vertex1] = (* board)[next_element];
                    root_queue.push_back(vertex1);
                    add_edge(root, vertex1, *connectedGraph);
                }
                    // we need to go fetch the vertexID for the element with the required position to complete our trail
                else{
                    int v_position{ getVertexPosition(*connectedGraph, *(*board)[next_element].position) };
                    add_edge(root, (*connectedGraph).vertex_set()[v_position], *connectedGraph);
                }
            }


        }
        // remove the top of the queue
        queue.pop_front();
        root_queue.pop_front();
    } // end of while loop
    // reset all the vertices isVisited to false;
    resetVisitedNodes();
    return connectedGraph;
}


void GBMap::printBoard() {
    cout << getBoardString();
}

void GBMap::resetVisitedNodes() {
    for(int i = 0; i < *SIZE;i++){
        *(*board)[i].isVisited = false;
    }
}

int GBMap::getVertexPosition(ResourceTrails graph, int position) const {
    for(int i = 0; i < num_vertices(graph); i++){
        if(*graph[i].position == position){
            return i;
        }
    }
    return -1;
}
bool GBMap::vertexContainedInQueue(deque<NodeID> queue, NodeID element) const {
    auto it = find(queue.begin(),queue.end(),element);
    return it != queue.end();
}
bool GBMap::createBoard() {
    if(*CONFIG == 0){
        for (int position = 0; position < *SIZE; position++) {
            add_vertex(*board);
            // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
            if (position > 0 && position % 5 != 0)
                add_edge(position, position - 1, *board);
            *(*board)[position].position = position;
        }

        for (int position = 0; position < 20; position++) {
            add_edge(position, position + 5, *board);
        }
    }
    else if(*CONFIG == 1){
        for (int position = 0; position < *SIZE; position++) {
            add_vertex(*board);
            // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
            if (position > 0 && position % 5 != 0)
                add_edge(position, position - 1, *board);
            *(*board)[position].position = position;
        }

        for (int position = 0; position < 30; position++) {
            add_edge(position, position + 5, *board);
        }
    }
    else if(*CONFIG==2){
        for (int position = 0; position < *SIZE; position++) {
            add_vertex(*board);
            *(*board)[position].position = position;
        }
        // now we need to add edges to all right most element (start at 0 then add edges towards the right... handle 1st row and last row seperatly)
        for(int i = 0; i < 4; i++){
            NodeID v1 = (*board).vertex_set()[i];
            NodeID v2 = (*board).vertex_set()[i+1];
            // get the vertex underneath it
            NodeID v3 = (*board).vertex_set()[i+6];
            add_edge(v1,v2, *board);
            add_edge(v1,v3, *board);
        }
        // do the last row
        for(int i = 40; i < 44; i++){
            NodeID v1 = (*board).vertex_set()[i];
            NodeID v2 = (*board).vertex_set()[i+1];
            NodeID v3 = (*board).vertex_set()[i-6];
            add_edge(v1,v2, *board);
            // add an edge to the vertex ontop of it it
            add_edge(v1,v3, *board);
        }
        // now do the rows inbetween
        for(int i = 5; i < 40; i++){
            // we need to exclude the last vertex of each row
            NodeID v1 = (*board).vertex_set()[i];
            if(i % 7 != 4) {
                NodeID v2 = (*board).vertex_set()[i + 1];
                // undirected graph order does not matter
                add_edge(v1, v2, *board);
                // last edge does not need to add an edge down since we already did it previously
            }
            if(i < 33){
                NodeID v3 = (*board).vertex_set()[i+7];
                add_edge(v1,v3, *board);
            }
        }
    }
    // return false if CONFIG not valid
    else
        return false;

    return true;
}

void GBMap::printIndexConfiguration() {
    if(*CONFIG == 2){
        cout << "BOARD LAYOUT FOR 4 Players" << "\n" <<" -  00 01 02 03 04--" <<"\n 05 06 07 08 09 10 11-"
             << "\n 12 13 14 15 16 17 18-" << "\n 19 20 21 22 23 24 25-" << "\n 26 27 28 29 30 31 32-" << "\n 33 34 35 36 37 38 39 "
             << "\n -  40 41 42 43 44 -" << endl;
    }
    else if(*CONFIG == 1){
        string config =" -  00 01 02 03 04 -\n";
        config.append(" -  05 06 07 08 09 -\n");
        config.append(" -  10 11 12 13 14 -\n");
        config.append(" -  15 16 17 18 19 -\n");
        config.append(" -  20 21 22 23 24 -\n");
        config.append(" -  25 26 27 28 29 -\n");
        config.append(" -  30 31 32 33 34 -\n");
        cout << config;
    }
    else{
        string config =" -  00 01 02 03 04 -\n";
        config.append(" -  05 06 07 08 09 -\n");
        config.append(" -  10 11 12 13 14 -\n");
        config.append(" -  15 16 17 18 19 -\n");
        config.append(" -  20 21 22 23 24 -\n");
        cout << config;
    }
}

void GBMap::assignDefaultTiles() {
    /*
     * Create 4 tiles
     */
    switch((*CONFIG)){
        case 0:
            /*
             * config 0 --- 0   4 20 24
             */
            placeHarvestTile(0, tl);
            *(*board)[0].isPlayed = true;
            placeHarvestTile(4,tr);
            *(*board)[4].isPlayed = true;
            placeHarvestTile(20, br);
            *(*board)[20].isPlayed = true;
            placeHarvestTile(24, bl);
            *(*board)[24].isPlayed = true;
            *playCounter = 4;
            break;
        case 1:
            /*
             * config 1 --- 5   9 25 29
             */
            placeHarvestTile(5, tl);
            *(*board)[5].isPlayed = true;
            placeHarvestTile(9,tr);
            *(*board)[9].isPlayed = true;
            placeHarvestTile(25, br);
            *(*board)[25].isPlayed = true;
            placeHarvestTile(29, bl);
            *(*board)[29].isPlayed = true;
            *playCounter = 4;
            break;
        case 2:
            /*
                 * config 1 --- 6   10 34 38
                 */
            placeHarvestTile(6, tl);
            *(*board)[6].isPlayed = true;
            placeHarvestTile(10,tr);
            *(*board)[10].isPlayed = true;
            placeHarvestTile(34, br);
            *(*board)[34].isPlayed = true;
            placeHarvestTile(38, bl);
            *(*board)[38].isPlayed = true;
            *playCounter = 4;
            break;
        default:
            /*
             * config 0 --- 0   4 20 24
             */
            placeHarvestTile(0, tl);
            *(*board)[0].isPlayed = true;
            placeHarvestTile(4,tr);
            *(*board)[4].isPlayed = true;
            placeHarvestTile(20, br);
            *(*board)[20].isPlayed = true;
            placeHarvestTile(24, bl);
            *(*board)[24].isPlayed = true;
            *playCounter = 4;
            break;
    }
}

string GBMap::castResourceTypesToString(ResourceTypes type) const{
    if(type == ResourceTypes::SHEEP)
        return "SH";
    else if(type == ResourceTypes::WOOD)
        return "WD";
    else if(type == ResourceTypes::STONE)
        return "ST";
    else
        return "WT";
}

HarvestTile * GBMap::getHarvestTile(int position) {
    return (*board)[position].tile;
}

bool GBMap::isGameOver(){
    return (*SIZE - *playCounter) == 1;
}

string GBMap::getBoardString() const {
    ostringstream gBoard;
    const string spacer{"    "};
    const string inner_spacer("  ");
    // Check config to determine #row
    int row_num{5};
    // if config is 3 or 4 players
    if(*CONFIG >= 1)
        row_num = 7;
    // we will iterate by row
    if(*CONFIG != 2){
        int col_num{5};
        for(int i{0}; i < row_num; i++){
            for(int j{i*5}; j <  (i * col_num) + col_num; j++){
                if(!*(*board)[j].isPlayed) {
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << inner_spacer;
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
                }else{
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[0]) << inner_spacer;
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[1]) << spacer;
                }
            }
            // new line
            gBoard << '\n';
            for(int j{i*5}; j < (i * col_num) + col_num; j++){
                if(!*(*board)[j].isPlayed) {
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << inner_spacer;
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
                }else{
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[3]) << inner_spacer;
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[2]) << spacer;
                }
            }
            gBoard << '\n' << '\n';
        }
    }else{
        // CONFIG == 2 has a special case where the first row and last row have only 5 elements rather than 7
        // As such those two rows must be handled seperately.
        int col_num{7};
        // perform on first row
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        for(int j{0}; j <  5; j++){
            if(!*(*board)[j].isPlayed) {
                gBoard << std::setfill('0') << std::setw(2)<<*(*board)[j].position << inner_spacer;
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
            }else{
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[0]) << inner_spacer;
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[1]) << spacer;
            }
        }
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        gBoard << '\n';
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        for(int j{0}; j < 5; j++){
            if(!*(*board)[j].isPlayed) {
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << inner_spacer;
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
            }else{
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[3]) << inner_spacer;
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[2]) << spacer;
            }
        }
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        gBoard << '\n' << '\n';

        // now we want to do as before but iterate on the next 5 rows
        for(int i{0}; i < 5; i++){
            for(int j{5 +(i*7)}; j < (i * col_num) + col_num + 5; j++){
                if(!*(*board)[j].isPlayed) {
                    gBoard << std::setfill('0') << std::setw(2)<<*(*board)[j].position << inner_spacer;
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
                }else{
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[0]) << inner_spacer;
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[1]) << spacer;
                }
            }
            // new line
            gBoard << '\n';
            for(int j{5 +(i*7)}; j < (i * col_num) + col_num + 5; j++){
                if(!*(*board)[j].isPlayed) {
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << inner_spacer;
                    gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
                }else{
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[3]) << inner_spacer;
                    gBoard << castResourceTypesToString((*board)[j].tile->tileContent[2]) << spacer;
                }
            }
            gBoard << '\n'<< '\n';
        }
        // perform on last row
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        for(int j{40}; j <  45; j++){
            if(!*(*board)[j].isPlayed) {
                gBoard << std::setfill('0') << std::setw(2)<<*(*board)[j].position << inner_spacer;
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
            }else{
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[0]) << inner_spacer;
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[1]) << spacer;
            }
        }
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        gBoard << '\n';
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        for(int j{40}; j < 45; j++){
            if(!*(*board)[j].isPlayed) {
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << inner_spacer;
                gBoard << std::setfill('0') << std::setw(2) << *(*board)[j].position << spacer;
            }else{
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[3]) << inner_spacer;
                gBoard << castResourceTypesToString((*board)[j].tile->tileContent[2]) << spacer;
            }
        }
        gBoard << "--" << inner_spacer;
        gBoard << "--" << spacer;
        gBoard << '\n' << '\n';
    }

    return gBoard.str();
}
