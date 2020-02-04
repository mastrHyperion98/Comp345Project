//
// Created by Steven on 2020-01-31.
//
#ifndef NEWHAVEN_GBMAP_H
#define NEWHAVEN_GBMAP_H

#endif //NEWHAVEN_GBMAP_H
#include "boost/graph/adjacency_list.hpp"
#include "GB_Tile.h"
// define a new type.... should probably be in its own header file to avoid having to add the map to everything

struct Square
{
public:
    GB_Tile *tile;
    int *position;
};
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Square> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
class GBMap{
    // declaring public methods and parameters
public:
    // class constructor
    GBMap();
    ~GBMap();
    int* GetBoardConfig();
    void SetBoardConfig(int config);
    Graph* GetGameBoard();
    void GenerateGraph();
    const int *number_centre_squares = new int(25);
private:
    // an int value in the range [0,2] denotes the initial configuration of the board
    // 0 = 2 players, 1 = 3 players, 2 = 4 players;
    int *board_configuration;
    Graph *game_board = new Graph;

};