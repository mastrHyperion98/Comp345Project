/*This file contains the functions and properties used by the New Haven Game Map.
 * The map is a connected graph implemented using the boost graph library.
 * Created by Steven on 2020-01-31.
 * Created for Concordia W 2020 Comp 345 New Haven Project
 */

// include boost adjacency_list
#include "boost/graph/adjacency_list.hpp"
#include <boost/graph/graph_utility.hpp>
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
int* GBMap::GetBoardConfig() {
    return GBMap::board_configuration;
}
// Define the function to set the board configuration
void GBMap::SetBoardConfig(int config) {
    // assign the value of config to our int pointer board_configuration
    GBMap::board_configuration = new int(config);
}
// Function that goes and fetches the graph
Graph* GBMap::GetGameBoard() {
    return GBMap::game_board;
}
// generate the graph
/*
The gameboard will be initiated in parts, based on the configuration of the board (aka # of players)
Each vertex (Square) will be labeled with a number. That number will be indentical to its index in the graph
and will start at 0 at the upper left most corner of the 2 player field. From there, the vertices will be created row by row.
It will be created in a similar way as a 2D Matrix. 
*/
void GBMap::GenerateGraph() {
    // Is it a 2 player game, if so initialize center board only. 
    if(*GBMap::GetBoardConfig() == 0){
        // Create the Center Field
        CreateCenterField();
    }
    else {
        cerr << "This FEATURE IS NOT YET IMPLEMENTED";
    }
}
// create the center 5x5 field area
void GBMap::CreateCenterField() {
 
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
void GBMap::CreateUpperLowerField() {
    // first check that the center field has been created
    for (int position = 25; position < 35; position++) {
        add_vertex(*game_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (position % 5 != 0)
            add_edge(position, position - 1, *game_board);
        (*game_board)[position].position = new int(position);
    }
    // add edges for the first and last row going down
    for(int position = 0; position < 5; position++){
        add_edge(position, position + 25, *game_board);
    }
    for(int position = 20; position < 25; position++){
        add_edge(position, position + 10, *game_board);
    }
}
Square GBMap::GetSquare(int position) {
    /*TO-DO
     * Verify position is within the appropriate ranged based on the board configuration
     * return an error otherwise.
     */
    return (*game_board)[position];
}
void GBMap::PrintGraph() {
    boost::print_graph(*game_board);
}



