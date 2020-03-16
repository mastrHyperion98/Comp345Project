#include "VGMap.h"
#include "Resources.h"
#include "ResourceScore.h"
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
    void drawBuilding(Building& building);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the harvest tile
    void drawHarvestTile(HarvestTile& tile);
    // im assuming this prints out the available resources;
    ResourceTracker resourceTracker();
    bool buildVillage();
    void calculateResources(ResourceTrails);

private:
    VGMap *village;
    ResourceTracker *resource_score;
    ScoreCalculator *vb_score;
    Hand *my_hand;

};
