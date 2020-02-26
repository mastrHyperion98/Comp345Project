//
// Created by Nizz Wizz on 2020-02-05.
// edited by Steven Smith on 2020-02-25
//

#ifndef NEWHAVEN_VGMAP_H
#define NEWHAVEN_VGMAP_H

#include "boost/graph/adjacency_list.hpp"
#include "Resources.h"
#include <string>

// Our vertex Data Circle that will contain all our needed information
class Circle{
public:
    // our public properties and methods
    bool *isVisited = new bool(false);
    Circle();
    ~Circle();
    int getRow() const;
    int getColumn() const;
    int getVCost() const;
    int getPosition() const;
    void setRow(int row);
    void setCol(int col);
    void setPosition(int pos);
    void setBuilding(Building * building);
    void setVCost(int cost);
    Building getBuilding() const;
    bool getIsPlayed() const;

    // our private properties and functions
private:
    int *position = nullptr;
    int *row = nullptr;
    int *column = nullptr;
    int *vCost = nullptr;
    Building* building = nullptr;
    bool *isPlayed = new bool(false);
};

// defune our village board graph
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Circle> Graph;
// define our vertex descriptor
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_v;
// define the graph we will be using for computing scores
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, Circle> ConnectedCircles;

using namespace std;
class VGMap {
public:
    // class constructor
    VGMap();
    ~VGMap();;
    void PrintGraph();
    void PrintConnectedGraph();
    void getCircle(int position);
    ConnectedCircles getConnectedRow(int const row);
    ConnectedCircles getConnectedColumn(int const col);
    void resetVisited();
private:
    void CreateVillageField();
    void GenerateGraph();
    Graph *village_board = new Graph;
};

#endif //NEWHAVEN_VGMAP_H
