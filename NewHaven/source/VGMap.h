//
// Created by Nizz Wizz on 2020-02-05.
//

#ifndef NEWHAVEN_VGMAP_H
#define NEWHAVEN_VGMAP_H

#include "boost/graph/adjacency_list.hpp"

#endif //NEWHAVEN_VGMAP_H

struct Circle{
public:
    int *position;
};


typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Circle> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;

class VGMap {
public:
    // class constructor
    VGMap();
    ~VGMap();
    Graph* GetVillageBoard();
    void GenerateGraph();
    void PrintGraph();
    void PrintConnectedGraph();
    const int *number_cirles = new int(25);

private:
    void CreateVillageField();
    Graph *village_board = new Graph;
};


