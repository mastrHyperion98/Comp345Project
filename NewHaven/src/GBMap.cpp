/*This file contains the functions and properties used by the New Haven Game Map.
 * The map is a connected graph implemented using the boost graph library.
 * Created by Steven on 2020-01-31.
 * Created for Concordia W 2020 Comp 345 New Haven Project
 */

// include boost adjacency_list
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/connected_components.hpp"
// include the io stream library
#include <iostream>
// include the string library
#include <string>
#include <deque>
// include GBMap header for functions calls etc.
#include "GBMap.h"
#include "Square.h"
#include <boost/graph/copy.hpp>
// we will be using the boost and std namespace
using namespace std;
using namespace boost;

// Define the constructor for the GameBoard Map
GBMap::GBMap() {
}
// Define the deconstructor of the GameBoard Map
GBMap::~GBMap()=default;
// return the pointer to the board configuration
int* GBMap::getBoardConfig() {
    return GBMap::board_configuration;
}
// Define the function to set the board configuration
void GBMap::setBoardConfig(int config) {
    if(config > 2 || config < 0)
        throw 3;
    // assign the value of config to our int pointer board_configuration
    GBMap::board_configuration = new int(config);
}
// Function that goes and fetches the graph
Graph GBMap::getGameBoard() {
    return *GBMap::game_board;
}
// generate the graph
/*
The gameboard will be initiated in parts, based on the configuration of the board (aka # of players)
Each vertex (Square) will be labeled with a number. That number will be indentical to its index in the graph
and will start at 0 at the upper left most corner of the 2 player field. From there, the vertices will be created row by row.
It will be created in a similar way as a 2D Matrix. 
*/
void GBMap::generateGraph() {
    // Is it a 2 player game, if so initialize center board only. 
    if(*GBMap::getBoardConfig() == 0){
        // Create the Center Field
        createCenterField();
        SIZE = new const int(25);
    }
    else if(*GBMap::getBoardConfig() == 1){
        createCenterField();
        createUpperLowerField();
        SIZE = new const int(35);
    }
    else if(*GBMap::getBoardConfig() == 2){
        createCenterField();
        createUpperLowerField();
        createLeftRightField();
        SIZE = new const int(45);
    }
    else{
        cerr << "ERROR: Board configuration :" << *GBMap::getBoardConfig() << " is not a valid configuration" << endl;
    }
}
// create the center 5x5 field area
void GBMap::createCenterField() {
 
    for (int position = 0; position < 25; position++) {
       add_vertex(*game_board);
       // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
       if (position > 0 && position % 5 != 0)
           add_edge(position, position - 1, *game_board);
        (*game_board)[position].setPosition(new int(position));
    }

    for (int position = 0; position < 20; position++) {
        add_edge(position, position + 5, *game_board);
    }
}
/*
 * Creates the upper and lower playing area for a 3 player map.
 *  Identification will start from 25 to 35 starting from the top row.
 */
void GBMap::createUpperLowerField() {
    // first check that the center field has been created
    for (int position = *GBMap().NUM_C_SQ; position < 35; position++) {
        add_vertex(*game_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (position % 5 != 0)
            add_edge(position, position - 1, *game_board);
        (*game_board)[position].setPosition(new int(position));
    }
    // add edges for the first and last row going down
    for(int position = 0; position < 5; position++){
        add_edge(position, position + *GBMap().NUM_C_SQ, *game_board);
    }
    for(int position = 20; position < 25; position++){
        add_edge(position, position + 10, *game_board);
    }
}
/*
 * Creates the left and right playing area for a 4 player configuration.
 * Identification will start from 35 to 44 and will start on the top left
 * -  25 26 27 28 29 --
 * 35 00 01 02 03 04 40
 * 36 05 06 07 08 09 41
 * 37 10 11 12 13 14 42
 * 38 15 16 17 18 19 43
 * 39 20 21 22 23 24 44
 * -  30 31 32 33 34 -
 */
void GBMap::createLeftRightField(){
    for(int position = 35; position < 45; position++){
        add_vertex(*game_board);
        if(position > 35)
            add_edge(position, position - 1, *game_board);
        (*game_board)[position].setPosition(new int(position));
    }
    // we need to add the edges -- is there some sort of rule.... we might need to add them by hand :(
    for(int position = 35, target = 0;position < 45; target += 5, position++){
        add_edge(position, target, *game_board);
        if(position == 39)
            target = -01;
    }
}
Square GBMap::getSquare(int position) {
    /*TO-DO
     * Verify position is within the appropriate ranged based on the board configuration
     * return an error otherwise.
     */
    return (*game_board)[position];
}
void GBMap::printGraph() {
    boost::print_graph(*game_board);
}

// Taken from the Boost Connected Graph Example
//https://www.boost.org/doc/libs/1_65_0/libs/graph/example/connected_components.cpp
// Prints the number of Connected Components and which vertex belongs to which component
// A component is a set of one or more nodes in which a path exists.
// In other words, if the graph is connected than there is only 1 component.
// If component 2 exists then there does not exists a path linking nodes from Component 1 and 2.
void GBMap::printConnectedGraph() {

    std::vector<int> component(num_vertices(*game_board));
    int num = connected_components(*game_board, &component[0]);

    std::vector<int>::size_type i;
    cout << "Total number of components: " << num << endl;
    for (i = 0; i != component.size(); ++i)
        cout << "Square " << i <<" is in component " << component[i] << endl;
    cout << endl;
}
/*
 * From a given origin compute a graph of connected played tiles
 */
ResourceTrails GBMap::getConnectedGraph(int const position){
        ResourceTrails connectedGraph;
        auto vertices = (*game_board).vertex_set();
        vertex_t first_v = vertices[position];
        vertex_t root = add_vertex(connectedGraph);
        connectedGraph[root] = (*game_board)[first_v];
        deque<vertex_t> queue;
        deque<vertex_t> root_queue;
        queue.push_back(first_v);
        root_queue.push_back(root);

        while(!queue.empty()) {
            Graph::adjacency_iterator neighbourIt, neighbourEnd;
            // origin of the current search
            vertex_t origin = queue.front();
            root = root_queue.front();
            // fetches references to the last vertex
            tie(neighbourIt, neighbourEnd) = adjacent_vertices(origin, *game_board);
            for (; neighbourIt != neighbourEnd; ++neighbourIt) {
                *(*game_board)[origin].isVisited = true;
                // next_element
                vertex_t next_element = vertices[*neighbourIt];
                // if the element has not been visited yet and is a playedTile add to the new graph and add to queue to
                // search its neighbours
                if (!*(*game_board)[next_element].isVisited && (*game_board)[next_element].getIsPlayed()){
                    if( !vertexContainedInQueue(queue, next_element))
                         queue.push_back(next_element);
                    if(!graphContainsPosition(connectedGraph, (*game_board)[next_element].getPosition())){
                        vertex_t vertex1 = add_vertex(connectedGraph);
                        connectedGraph[vertex1] = (*game_board)[next_element];
                        root_queue.push_back(vertex1);
                        add_edge(root, vertex1, connectedGraph);
                    }
                    // we need to go fetch the vertexID for the element with the required position to complete our trail
                    else{
                        int v_position = getVertexPosition(connectedGraph, (*game_board)[next_element].getPosition());
                        add_edge(root, connectedGraph.vertex_set()[v_position], connectedGraph);
                    }
                }
            }
            // remove the top of the queue
            queue.pop_front();
            root_queue.pop_front();
        } // end of while loop
        // reset all the vertices isVisited to false;
        resetVerticesVisited();
    return connectedGraph;
}
/*
 * The function resetVerticesVisited traverses the graph and sets all the square isVisited data to false
 */
void GBMap::resetVerticesVisited() {
    for(int i = 0; i < *SIZE; i++){
        *(*game_board)[i].isVisited = false;
    }
}
bool GBMap::vertexContainedInQueue(deque<vertex_t> queue, vertex_t element) const{
    auto it = find(queue.begin(),queue.end(),element);
    return it != queue.end();
}
bool GBMap::graphContainsPosition(ResourceTrails graph, int position) const{
   for(int i = 0; i < num_vertices(graph); i++){
      if(graph[i].getPosition() == position){
            return true;
      }
   }return false;
}
int GBMap::getVertexPosition(ResourceTrails graph, int position) const{
    for(int i = 0; i < num_vertices(graph); i++){
        if(graph[i].getPosition() == position){
            return i;
        }
    }
    cerr << "ERROR: position not in Graph" << endl;
    return 1;
}

