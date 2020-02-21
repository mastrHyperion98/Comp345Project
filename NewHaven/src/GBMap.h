//
// Created by Steven on 2020-01-31.
// Concordia W 2020 Comp 345
//

#ifndef NEWHAVEN_GBMAP_H
#define NEWHAVEN_GBMAP_H
#include "boost/graph/adjacency_list.hpp"
#include <deque>
#include "Resources.h"
#include "Square.h"

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Square> Graph;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, Square> ResourceTrails;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

using namespace std;

class GBMap{
    // declaring public methods and parameters
public:
    int getBoardConfig();
    int const *SIZE;
    const int *NUM_C_SQ = new int(25);

    // class constructor
    GBMap(int config);
    ~GBMap();
    void printGraph();
    void printConnectedGraph();
    // number of center squares
    Square getSquare(int position);
    ResourceTrails getConnectedGraph(int position);
private:
    // an int value in the range [0,2] denotes the initial configuration of the board
    // 0 = 2 players, 1 = 3 players, 2 = 4 players;
    int *board_configuration;
    Graph *game_board = new Graph;
    void generateGraph();
    void createCenterField();
    void createUpperLowerField();
    void createLeftRightField();
    void resetVerticesVisited();
    bool vertexContainedInQueue(deque<vertex_t> queue, vertex_t element) const;
    bool graphContainsPosition(ResourceTrails graph, int position) const;
    int getVertexPosition(ResourceTrails graph, int position) const;
};

#endif //NEWHAVEN_GBMAP_H