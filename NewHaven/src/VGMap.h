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
#include "GameObservers.h"
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

enum VG_State{BUILDING_PLAYED, BUILDING_PLAYED_FLIPPED, NILL};

using namespace std;
class VGMap: public Observable{
public:
    // class constructor
    VGMap(string);
    VGMap(const VGMap &map);
    VGMap &operator=(const VGMap &map);
    ~VGMap();
    void PrintGraph();
    bool isPlayed(int position);
    bool setBuilding(int position, Building *building);
    int getPositionCost(int position);
    ConnectedCircles getConnectedRow(int const row);
    ConnectedCircles getConnectedColumn(int const col);
    void resetVisited();
    string getName();
    int getNumUnplayed();
    VG_State getState(){return *state;};
    Circle *last_played;
    string getBoardString() const;
private:
    string *name;
    void CreateVillageField();
    C_Graph *village_board;
    map<ResourceTypes, bool> *typePlayed;
    bool isAdjacentType(ResourceTypes type, int position);
    string castResourceTypesToString(ResourceTypes) const;
    int *playCounter{new int(0)};
    const int *const SIZE{new const int{30}};
    bool playBuildingFlipped(Building* building, ResourceTypes type, int position);
    bool playBuilding(Building* building, ResourceTypes type, int position);
    VG_State * state;
    void setState(VG_State);
};

#endif //NEWHAVEN_VGMAP_H
