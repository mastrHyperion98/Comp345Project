//
// Created by Nizz Wizz on 2020-02-05.
// edited by Steven Smith on 2020-02-25
//

#ifndef NEWHAVEN_VGMAP_H
#define NEWHAVEN_VGMAP_H

#include "boost/graph/adjacency_list.hpp"
#include "Resources.h"
#include <string>
#include <map>

// Our vertex Data Circle that will contain all our needed information
class Circle{
public:
    // our public properties and methods
    bool *isVisited = new bool(false);
    Circle();
    Circle(const Circle &circle);
    Circle &operator=(const Circle &circle);
    ~Circle();
    int *position;
    int *row;
    int *column;
    int *vCost;
    Building* building;
    bool *isPlayed;
};

// define our village board graph
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Circle> C_Graph;
// define our vertex descriptor
typedef boost::graph_traits<C_Graph>::vertex_descriptor vertex_v;
// define the graph we will be using for computing scores
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, Circle> ConnectedCircles;

using namespace std;
class VGMap {
public:
    // class constructor
    VGMap();
    VGMap(const VGMap &map);
    VGMap &operator=(const VGMap &map);
    ~VGMap();
    void PrintGraph();
    void PrintConnectedGraph();
    bool isPlayed(int position);
    bool setBuilding(int position, Building *building);
    int getPositionCost(int position);
    ConnectedCircles getConnectedRow(int const row);
    ConnectedCircles getConnectedColumn(int const col);
    void resetVisited();
private:
    void CreateVillageField();
    C_Graph *village_board;
    map<ResourceTypes, bool> *typePlayed;
    bool isAdjacentType(ResourceTypes type, int position);

};

#endif //NEWHAVEN_VGMAP_H
