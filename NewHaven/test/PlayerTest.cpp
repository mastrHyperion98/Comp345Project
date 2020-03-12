//
// Created by hyperion on 2020-03-08.
//
#include "GBMap.h"
#include "Resources.h"
#include "Player.h"

int main(){
    GBMap map(0);
    ResourceTypes *types1 = new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP};
    ResourceTypes *types2 = new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP};
    Building building1{ResourceTypes::SHEEP, 3};
    Building building2{ResourceTypes::SHEEP, 4};
    Building building3{ResourceTypes::STONE, 5};
    HarvestTile tile{types1};
    HarvestTile tile2{types2};
    Player player;
    player.drawHarvestTile(tile);
    player.drawHarvestTile(tile2);
    player.drawBuilding(building1);
    player.drawBuilding(building2);
    player.drawBuilding(building3);
    int pos = player.placeHarvestTile();
    int re = player.calculateResources(*map.getResourcedGraph(pos));
    cout << re[0] << "\t" << re[1]<< "\t" << re[2] << "\t" << re[3] << endl;
    pos = player.placeHarvestTile();
    delete re;
    re = nullptr;
    re = player.calculateResources(*map.getResourcedGraph(pos));
    cout << re[0] << "\t" << re[1]<< "\t" << re[2] << "\t" << re[3] << endl;
    player.resourceTracker().printScore();
    /*for(int i = 0; i < 3; i++){
        player.buildVillage();
    }*/
}