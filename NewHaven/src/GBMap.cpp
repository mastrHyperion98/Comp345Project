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

GBMap::GBMap(int configuration):CONFIG(new const int(configuration)), SIZE(new const int(25 + (*CONFIG*10))){
    board = new GameBoard();
    // populate board
    if(!createBoard())
        // create a proper exception maybe
        throw 1;
}
GBMap::GBMap(const GBMap &map) : CONFIG(new const int(*map.CONFIG)), SIZE(new const int(25 + (*map.CONFIG*10))){
    // call the copy constructor of the GameBoard
    board = new GameBoard(*map.board);
}
GBMap::~GBMap(){
    delete CONFIG;
    delete SIZE;
    delete board;
}
GBMap & GBMap::operator=(const GBMap &map) {
// needs to be defined ahaha not done yet lol

}
bool GBMap::placeHarvestTile(int NodeID, HarvestTile &tile) {
 if(NodeID > *SIZE || NodeID < 0)
     return false;
    // should use the operator overload
    (*board)[NodeID].tile = new HarvestTile(tile);
    *(*board)[NodeID].isPlayed = true;
    return true;
}
ResourceTrails * GBMap::getResourcedGraph(int position) {
    // create a copy of the game_board
    // and use the copy throughout
    ResourceTrails *connectedGraph = new ResourceTrails;
    auto vertices = (*board).vertex_set();
    NodeID first_v = vertices[position];
    NodeID root = add_vertex(*connectedGraph);
    // copy the squares! IMPORTANT!
    (*connectedGraph)[root] = Square((*board)[first_v]);
    deque<NodeID> queue;
    deque<NodeID> root_queue;
    queue.push_back(first_v);
    root_queue.push_back(root);

    while(!queue.empty()) {
        GameBoard::adjacency_iterator neighbourIt, neighbourEnd;
        // origin of the current search
        NodeID origin = queue.front();
        root = root_queue.front();
        // fetches references to the last vertex
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(origin, *board);
        for (; neighbourIt != neighbourEnd; ++neighbourIt) {
            *(*board)[origin].isVisited = true;
            // next_element
            NodeID next_element = vertices[*neighbourIt];
            // if the element has not been visited yet and is a playedTile add to the new graph and add to queue to
            // search its neighbours
            if (!*(*board)[next_element].isVisited && *(*board)[next_element].isPlayed){
                if( !vertexContainedInQueue(queue, next_element))
                    queue.push_back(next_element);

                if(getVertexPosition(*connectedGraph, *(*board)[next_element].position) < 0){
                    NodeID vertex1 = add_vertex(*connectedGraph);
                    (*connectedGraph)[vertex1] = Square((* board)[next_element]);
                    root_queue.push_back(vertex1);
                    add_edge(root, vertex1, *connectedGraph);
                }
                    // we need to go fetch the vertexID for the element with the required position to complete our trail
                else{
                    int v_position = getVertexPosition(*connectedGraph, *(*board)[next_element].position);
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
    boost::print_graph(*board);
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