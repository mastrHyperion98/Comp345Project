//
// Created by Steven on 2020-01-31.
// Concordia W 2020 Comp 345
//

#ifndef NEWHAVEN_GBMAP_H
#define NEWHAVEN_GBMAP_H
#include "boost/graph/adjacency_list.hpp"
#include <deque>
#include <vector>
#include "Resources.h"
#include "Square.h"
#include <string>
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Square> GameBoard;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::bidirectionalS, Square> ResourceTrails;
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
    bool placeHarvestTile(int NodeID,HarvestTile *tile);
    ResourceTrails* getResourcedGraph(int position);
    void printBoard();
    void printIndexConfiguration();
    HarvestTile* getHarvestTile(int);
    bool isGameOver();
private:
    GameBoard* board;
    std::vector<Building*>* buildings;
    HarvestTile *tl{new HarvestTile(new ResourceTypes[4]{ResourceTypes::STONE, ResourceTypes ::SHEEP, ResourceTypes::WOOD, ResourceTypes::WOOD})};
    HarvestTile *tr{new HarvestTile(new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes ::SHEEP, ResourceTypes::WHEAT, ResourceTypes::WOOD})};
    HarvestTile *bl{new HarvestTile(new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes ::STONE, ResourceTypes::SHEEP, ResourceTypes::WHEAT})};
    HarvestTile *br{new HarvestTile(new ResourceTypes[4]{ResourceTypes::STONE, ResourceTypes ::STONE, ResourceTypes::WOOD, ResourceTypes::WHEAT})};
    bool createBoard();
    inline void resetVisitedNodes();
    inline bool vertexContainedInQueue(deque<NodeID> queue, NodeID element) const;
    inline int getVertexPosition(ResourceTrails graph, int position) const;
    void assignDefaultTiles();
    string castResourceTypesToString(ResourceTypes);
    int *playCounter{new int(0)};
};

#endif //NEWHAVEN_GBMAP_H