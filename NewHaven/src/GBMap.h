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

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Square> GameBoard;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, Square> ResourceTrails;
typedef boost::graph_traits<GameBoard>::vertex_descriptor NodeID;


using namespace std;
class GBMap{
    // declaring public methods and parameters
public:
    GBMap();
    GBMap(int configuration);
    GBMap(const GBMap &map);
    ~GBMap();
    const int* const CONFIG;
    const int * const SIZE;
    static GBMap *current_map;
    bool placeHarvestTile(int NodeID,HarvestTile &tile);
    ResourceTrails* getResourcedGraph(int position);
    void printBoard();
    void printIndexConfiguration();
private:

    GameBoard* board;
    bool createBoard();
    inline void resetVisitedNodes();
    inline bool vertexContainedInQueue(deque<NodeID> queue, NodeID element) const;
    inline int getVertexPosition(ResourceTrails graph, int position) const;
};

#endif //NEWHAVEN_GBMAP_H