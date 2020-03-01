#include "../src/Player.h"

int main(){
    Player* player = new Player();
    HarvestDeck* hDeck = new HarvestDeck();
    BuildingDeck* bDeck = new BuildingDeck();
    ResourceScore* resScore = new ResourceScore();

    player->drawHarvestTile(hDeck);
    player->drawBuilding(bDeck);

    player->calculateResources(resScore);
    player->resourceTracker(resScore);
}