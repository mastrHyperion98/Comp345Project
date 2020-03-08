#include "VGMap.h"
#include "Resources.h"
#include "ResourceScore.h"
#include "ScoreCalculator.h"

struct Player
{
public:
    Player();
    Player(const Player &player);
    ~Player();
    Player &operator = (const Player &player);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the game_board
    bool placeHarvestTile(HarvestTile&, int);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the building deck
    inline void drawBuilding();
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the harvest tile
    inline void drawHarvestTile();
    // im assuming this prints out the available resources;
    inline void resourceTracker();
    bool buildVillage(Building&, int);
    inline void calculateResources(ResourceTrails);

private:
    VGMap *village;
    ResourceScore *resource_score;
    ScoreCalculator *vb_score;
    Hand *my_hand;

};
