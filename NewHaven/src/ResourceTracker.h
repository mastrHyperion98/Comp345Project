//
// Created by hyperion on 2020-02-27.
//

#ifndef NEWHAVEN_RESOURCETRACKER_H
#define NEWHAVEN_RESOURCETRACKER_H
#include <map>
#include "GameObservers.h"
#include "GameController.h"
#include "deque"

class Setting;
using namespace std;
class ResourceTracker : public Observer {
public:

    ResourceTracker();
    ~ResourceTracker();
    ResourceTracker(const ResourceTracker& tracker);
    ResourceTracker& operator=(const ResourceTracker& scores);
    void computeScore(ResourceTrails trail);
    void printScore();
    bool consumeResources(ResourceTypes, std::uint_least16_t);
    bool hasResources(ResourceTypes, std::uint_least16_t);
    bool isEmpty();
    void reset();
    map<ResourceTypes, std::uint_least16_t> getScore();
    void update();
private:
    struct Quad{
        Quad();
        Quad(const Quad&);
        ~Quad();
        Quad &operator=(const Quad & quad);
        bool *isMatching;
        // prevent infinite loop
       const int * const MAX_VISIT = new const int(100);
       int *current_visit_count;

    };
    typedef std::map<NodeID, Quad*> Map;
    typedef std::pair<NodeID, Quad*> Pair;
    std::map<ResourceTypes, std::uint_least16_t>* score;
    void setQuadInner(Quad *quad, ResourceTypes* resource, int direction);
    inline void addResources(ResourceTypes type);
    const int  *DOWN = new int(-5);
    const int *UP = new int(5);
    const int  *LEFT = new int(1);
    const int  *RIGHT = new int(-1);
    void backstepping(NodeID root, Map *map,ResourceTrails&);

};


#endif //NEWHAVEN_RESOURCETRACKER_H
