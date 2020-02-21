//
// Created by Nizz Wizz on 2020-02-05.
//

#ifndef NEWHAVEN_VGMAP_H
#define NEWHAVEN_VGMAP_H

#include "boost/graph/adjacency_list.hpp"

#endif //NEWHAVEN_VGMAP_H
//enum face {up, down, none};
struct Circle{
public:
    int *row = nullptr;
    int *column = nullptr;
    int *vCost = nullptr;
    bool *isVisited = new bool(false);
};


typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Circle> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_v;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, Circle> ConnectedCircles;


class VGMap {
public:
    // class constructor
    VGMap();
    ~VGMap();;
    void GenerateGraph();
    void PrintGraph();
    void PrintConnectedGraph();
    void CalcScore();
    ConnectedCircles getConnectedRow(int const row);
    ConnectedCircles getConnectedColumn(int const col);
    void resetVisited();
private:
    void CreateVillageField();
    Graph *village_board = new Graph;
};


