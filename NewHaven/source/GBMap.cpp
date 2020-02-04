/*This file contains the functions and properties used by the New Haven Game Map.
 * The map is a connected graph implemented using the boost graph library.
 * Created by Steven on 2020-01-31.
 * Created for Concordia W 2020 Comp 345 New Haven Project
 */

// include boost adjacency_list
#include "boost/graph/adjacency_list.hpp"
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
    GBMap::board_configuration = &config;
}
// Function that goes and fetches the graph
Graph* GBMap::GetGameBoard() {
    return GBMap::game_board;
}
// generate the graph
void GBMap::GenerateGraph() {
    // create the centre 25 nodes
    if(*GBMap::GetBoardConfig() == 0){
            vertex_t v1 = add_vertex(*game_board);
        (*game_board)[v1].position = new int(10);
        cout << "vertex name " << *(*game_board)[v1].position << std::endl;
    }
}


