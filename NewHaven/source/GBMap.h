//
// Created by Steven on 2020-01-31.
//
#ifndef NEWHAVEN_GBMAP_H
#define NEWHAVEN_GBMAP_H

#endif //NEWHAVEN_GBMAP_H
#import "boost/graph/adjacency_list.hpp";
// define a new type.... should probably be in its own header file to avoid having to add the map to everything
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS> Graph;
struct Square
{
private:
    GB_Tile *tile;
    int *position;

public:
    GB_Tile* GetTile();
    int* GetPosition();
    void SetTile(GB_Tile *tile);
    void SetPosition(int position);
};


class GBMap{
    // declaring public methods and parameters
public:
    // class constructor
    GBMap();
    ~GBMap();
    int* GetBoardConfig();
    void SetBoardConfig(int config);
    Graph* GetGameBoard();
private:
    // an int value in the range [0,2] denotes the initial configuration of the board
    // 0 = 2 players, 1 = 3 players, 2 = 4 players;
    int *board_configuration;
    Graph *game_board;

};