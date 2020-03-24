#include "VGMap.h"
#include "Resources.h"
#include "ScoreCalculator.h"
#include "ResourceTracker.h"

struct Player
{
public:
    Player();
    Player(const Player &player);
    ~Player();
    Player &operator = (const Player &player);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the game_board
    int placeHarvestTile();
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the building deck
    void drawBuilding(Building* building);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the harvest tile
    void drawHarvestTile(HarvestTile* tile);
    void drawBuildingPool(Building*);
    // Returns the ResourceTracker object held by the player
    ResourceTracker* resourceTracker();
    bool buildVillage();
    void calculateResources(ResourceTrails);
    void setShipmentTile(HarvestTile* tile);
    void setVillage(VGMap);
private:
    VGMap *village;
    ResourceTracker *resource_score;
    ScoreCalculator *vb_score;
    Hand *my_hand;

};
