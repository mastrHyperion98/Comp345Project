#include "../src/Resources.h"
#include "../src/GBMap.h"

struct ResourcesCollected
{
    public:
        int mapSize;
        vector<int> connectedNodes;
        int position;
        map<int, ResourceTypes*> tiles;
        void calculateResourcesCollected();
        bool checkRight(int currentPosition);
        bool checkLeft(int currentPosition);
        bool checkBelow(int currentPosition);
        bool checkAbove(int currentPosition);
        int checkRightAndBelow(ResourceTypes mainResource, ResourceTypes rightResource, ResourceTypes bottomResource);
        int checkLeftAndBelow(ResourceTypes mainResource, ResourceTypes leftResource, ResourceTypes bottomResource);
        int checkRightAndAbove(ResourceTypes mainResource, ResourceTypes rightResource, ResourceTypes aboveResource);
        int checkLeftAndAbove(ResourceTypes mainResource, ResourceTypes leftResource, ResourceTypes aboveResource);
};

//struct BuildingScore
//{
//    private:
//        Building* buildings;
//    public:
//        void calculateBuildingScore();
//};