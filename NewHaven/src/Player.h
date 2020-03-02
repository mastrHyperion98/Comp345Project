#include "VGMap.h"
#include "Resources.h"
#include "ResourceScore.h"

struct Player
{
public:
    Player();
    ~Player();

    VGMap* villageGameBoard;
    Hand* hand;
    std::map<ResourceTypes, std::uint_least16_t>* score;

    void placeHarvestTile();
    void drawBuilding(BuildingDeck* buildingDeck);
    void drawHarvestTile(HarvestDeck* harvestDeck);
    void resourceTracker(ResourceScore* resourceScore);
    void buildVillage();
    void calculateResources(ResourceScore* resourceScore);
};
