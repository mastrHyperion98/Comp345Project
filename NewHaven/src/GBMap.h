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
typedef boost::graph_traits<ResourceTrails>::vertex_descriptor ResourceNode;


using namespace std;
class GBMap{
    // declaring public methods and parameters
public:
    GBMap(int configuration);
    GBMap(const GBMap &map);
    GBMap &operator=(const GBMap &map);
    ~GBMap();
    bool placeHarvestTile(int NodeID);
    ResourceTrails* getResourcedGraph(int position);
    inline void printBoard();

private:
    const int* const CONFIG;
    const int * const SIZE;
    GameBoard* board;
    bool createBoard();
    inline void resetVisitedNodes();
    inline bool vertexContainedInQueue(deque<NodeID> queue, NodeID element) const;
    inline int getVertexPosition(ResourceTrails graph, int position) const;
};

#endif //NEWHAVEN_GBMAP_H