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
#include "GB_Tile.h"
// include GBMap header for functions calls etc.
#include "GBMap.h"
// we will be using the boost and std namespace
using namespace std;
using namespace boost;

// Define the function to return a game board tile held by the square
GB_Tile * Square::GetTile() {
    return Square::tile;
}
// Define and returns the position of the square on the gameboard
int* Square::GetPosition() {
    return Square::position;
}
// Define and Accepts a pointer to a GB_Tile object and assigns it to the square
void Square::SetTile(GB_Tile *tile) {
    Square::tile = tile;
}
// Define and accept and integer that is assigned as the squares position on the board.
void Square::SetPosition(int position) {
    Square::position = &position;
}

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



