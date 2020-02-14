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
// include GBMap header for functions calls etc.
#include "GBMap.h"
// we will be using the boost and std namespace
using namespace std;
using namespace boost;

// Define the constructor for the GameBoard Map
GBMap::GBMap() {
}
// Define the deconstructor of the GameBoard Map
GBMap::~GBMap() = default;

// return the pointer to the board configuration
int* GBMap::getBoardConfig() {
    return GBMap::board_configuration;
}
// Define the function to set the board configuration
void GBMap::setBoardConfig(int config) {
    // assign the value of config to our int pointer board_configuration
    GBMap::board_configuration = new int(config);
}
// Function that goes and fetches the graph
Graph* GBMap::getGameBoard() {
    return GBMap::game_board;
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
    }
    else if(*GBMap::getBoardConfig() == 1){
        createCenterField();
        createUpperLowerField();
    }
    else if(*GBMap::getBoardConfig() == 2){
        createCenterField();
        createUpperLowerField();
        createLeftRightField();
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
        (*game_board)[position].position = new int(position);
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
    for (int position = *GBMap().number_centre_squares; position < 35; position++) {
        add_vertex(*game_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (position % 5 != 0)
            add_edge(position, position - 1, *game_board);
        (*game_board)[position].position = new int(position);
    }
    // add edges for the first and last row going down
    for(int position = 0; position < 5; position++){
        add_edge(position, position + *GBMap().number_centre_squares, *game_board);
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
        (*game_board)[position].position = new int(position);
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


