#include "VGMap.h"
#include "Resources.h"
#include "ResourceScore.h"

struct Player
{
private:
    VGMap* villageGameBoard;
    Hand* hand;
    std::map<ResourceTypes, std::uint_least16_t>* score;

public:
    Player();
    ~Player();

    void placeHarvestTile();
    void drawBuilding();
    void drawHarvestTile();
    void resourceTracker();
    void buildVillage();
    void calculateResources();
};
