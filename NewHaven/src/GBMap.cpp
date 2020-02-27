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
GBMap::GBMap(int config) {
    if(config > 2 || config < 0)
        throw 3;
    this->board_configuration = new int(config);
    generateGraph();
}
// Define the deconstructor of the GameBoard Map
GBMap::~GBMap()=default;
// return the pointer to the board configuration
int GBMap::getBoardConfig() {
    return *GBMap::board_configuration;
}

// Function that goes and fetches the graph
// generate the graph
/*
The gameboard will be initiated in parts, based on the configuration of the board (aka # of players)
Each vertex (Square) will be labeled with a number. That number will be indentical to its index in the graph
and will start at 0 at the upper left most corner of the 2 player field. From there, the vertices will be created row by row.
It will be created in a similar way as a 2D Matrix. 
*/
void GBMap::generateGraph() {
    // Is it a 2 player game, if so initialize center board only. 
    if(*this->board_configuration == 0){
        // Create the Center Field
        SIZE = new const int(25);
        generateTwoPlayerBoard();

    }
    else if(*this->board_configuration == 1){
        SIZE = new const int(35);
        generateThreePlayerBoard();

    }
    else if(*this->board_configuration == 2){
        SIZE = new const int(45);
       generateFourPlayerBoard();
    }
    else{
        cerr << "ERROR: Board configuration :" << *this->board_configuration << " is not a valid configuration" << endl;
    }
}
// create the center 5x5 field area
void GBMap::generateTwoPlayerBoard() {
 
    for (int position = 0; position < *SIZE; position++) {
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
 *  Identification will start from 0 to 35 starting from the top row.
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 * -  26 27 28 29 30 -
 * -  31 32 33 34 35 -
 */
void GBMap::generateThreePlayerBoard(){
    // first check that the center field has been created
    for (int position = 0; position < *SIZE; position++) {
        add_vertex(*game_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (position > 0 && position % 5 != 0)
            add_edge(position, position - 1, *game_board);
        (*game_board)[position].setPosition(new int(position));
    }

    for (int position = 0; position < 30; position++) {
        add_edge(position, position + 5, *game_board);
    }
}
/*
 * Creates the left and right playing area for a 4 player configuration.
 * Identification will start from 35 to 44 and will start on the top left
 * -  00 01 02 03 04--
 * 05 06 07 08 09 10 11-
 * 12 13 14 15 16 17 18-
 * 19 20 21 22 23 24 25-
 * 26 27 28 29 30 31 32-
 * 33 34 35 36 37 38 39 -
 * -  40 41 42 43 44 -
 * // two exceptions (1st row and the last row as such do the edges them seperately
 */
void GBMap::generateFourPlayerBoard(){

    for (int position = 0; position < *SIZE; position++) {
        add_vertex(*game_board);
        (*game_board)[position].setPosition(new int(position));
    }
 // now we need to add edges to all right most element (start at 0 then add edges towards the right... handle 1st row and last row seperatly)
 for(int i = 0; i < 4; i++){
     vertex_t v1 = (*game_board).vertex_set()[i];
     vertex_t v2 = (*game_board).vertex_set()[i+1];
     // get the vertex underneath it
     vertex_t v3 = (*game_board).vertex_set()[i+6];
     add_edge(v1,v2, *game_board);
     add_edge(v1,v3, *game_board);
 }
 // do the last row
 for(int i = 40; i < 44; i++){
     vertex_t v1 = (*game_board).vertex_set()[i];
     vertex_t v2 = (*game_board).vertex_set()[i+1];
     vertex_t v3 = (*game_board).vertex_set()[i-6];
     add_edge(v1,v2, *game_board);
     // add an edge to the vertex ontop of it it
     add_edge(v1,v3, *game_board);
 }
 // now do the rows inbetween
    for(int i = 5; i < 40; i++){
        // we need to exclude the last vertex of each row
        vertex_t v1 = (*game_board).vertex_set()[i];
        if(i % 7 != 4) {
            vertex_t v2 = (*game_board).vertex_set()[i + 1];
            // undirected graph order does not matter
            add_edge(v1, v2, *game_board);
            // last edge does not need to add an edge down since we already did it previously
        }
        if(i < 33){
            vertex_t v3 = (*game_board).vertex_set()[i+7];
            add_edge(v1,v3, *game_board);
        }
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
        vertex_t vertex = (*game_board).vertex_set()[i];
        *(*game_board)[vertex].isVisited = false;
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
void GBMap::printIndexConfiguration() {
    if(*board_configuration == 2){
        cout << "BOARD LAYOUT FOR 4 Players" << "\n" <<" -  00 01 02 03 04--" <<"\n 05 06 07 08 09 10 11-"
             << "\n 12 13 14 15 16 17 18-" << "\n 19 20 21 22 23 24 25-" << "\n 26 27 28 29 30 31 32-" << "\n 33 34 35 36 37 38 39 "
             << "\n -  40 41 42 43 44 -" << endl;
    }
    else if(*board_configuration == 1){
        string config =" -  00 01 02 03 04 -\n";
        config.append(" -  05 06 07 08 09 -\n");
        config.append(" -  10 11 12 13 14 -\n");
        config.append(" -  15 16 17 18 19 -\n");
        config.append(" -  21 22 23 24 25 -\n");
        config.append(" -  26 27 28 29 30 -\n");
        config.append(" -  31 32 33 34 35 -\n");
      cout << config;
    }
    else{
        string config =" -  00 01 02 03 04 -\n";
        config.append(" -  05 06 07 08 09 -\n");
        config.append(" -  10 11 12 13 14 -\n");
        config.append(" -  15 16 17 18 19 -\n");
        config.append(" -  21 22 23 24 25 -\n");
        cout << config;
    }
}

void GBMap::setTile(int position, HarvestTile *tile) {
    (*game_board)[position].setTile(tile);
}
