//
// Created by hyperion on 2020-02-27.
//

#ifndef NEWHAVEN_RESOURCECALCULATOR_H
#define NEWHAVEN_RESOURCECALCULATOR_H
#include <map>
#include "GBMap.h"
#include "deque"
#include <boost/graph/reverse_graph.hpp>
using ReversedGraph = boost::reverse_graph<ResourceTrails,ResourceTrails&>;
using namespace std;
class ResourceCalculator {
public:
    ResourceCalculator();
    ~ResourceCalculator();
    int* computeResources(ResourceTrails trail);
    int *resources;
private:
    struct Quad{
        bool *isMatching = {new bool[4]{false,false,false,false}};
        // prevent infinite loop
        int const *MAX_VISIT = new int(4);
        int *current_visit_count = new int(0);
    };
    inline void setQuadInner(Quad quad, ResourceTypes* resource, int direction);
    inline void addResources(ResourceTypes type);
    const int  *DOWN = new int(-5);
    const int *UP = new int(5);
    const int  *LEFT = new int(1);
    const int  *RIGHT = new int(-1);
    const int *WHEAT = new int(0);
    const int *SHEEP = new int(1);
    const int *WOOD = new int(2);
    const int *STONE = new int(3);
    void backstepping(NodeID root, map<NodeID, Quad> map, ReversedGraph &trail,  ResourceTrails &graph);

};


#endif //NEWHAVEN_RESOURCECALCULATOR_H
