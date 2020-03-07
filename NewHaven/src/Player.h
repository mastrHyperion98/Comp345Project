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
    bool placeHarvestTile();
    inline void drawBuilding();
    inline void drawHarvestTile();
    // im assuming this prints out the available resources;
    inline void resourceTracker();
    void buildVillage();
    void calculateResources();

private:
    VGMap *village;
    ResourceScore *resource_score;
    ScoreCalculator *vb_score;
    Hand *my_hand;

};
