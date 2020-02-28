//
// Created by hyperion on 2020-02-27.
//

#ifndef NEWHAVEN_RESOURCECALCULATOR_H
#define NEWHAVEN_RESOURCECALCULATOR_H
#include <map>
#include "GBMap.h"
#include "deque"

using namespace std;
class ResourceCalculator {
public:
    ResourceCalculator();
    ~ResourceCalculator();
    int* computeResources(ResourceTrails trail);
private:
    class Quad{
    public:
        Quad();
        Quad(const Quad &quad);
        ~Quad();
        bool *isMatching = {new bool[4]};
        // prevent infinite loop
        int const *MAX_VISIT = new int(4);
        int *current_visit_count = new int(0);
    };
    inline void setQuadInner(int* arr, Quad *quad, ResourceTypes* resource, int direction);
    inline void addResources(int* arr, ResourceTypes type);
    const int  *DOWN = new int(-5);
    const int *UP = new int(5);
    const int  *LEFT = new int(1);
    const int  *RIGHT = new int(-1);
    const int *WHEAT = new int(0);
    const int *SHEEP = new int(1);
    const int *WOOD = new int(2);
    const int *STONE = new int(3);

};


#endif //NEWHAVEN_RESOURCECALCULATOR_H
