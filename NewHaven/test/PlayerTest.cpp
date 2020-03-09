//
// Created by hyperion on 2020-03-08.
//
#include "GBMap.h"
#include "Resources.h"
#include "Player.h"

int main(){
    GBMap map(0);
    ResourceTypes *types1 = new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::SHEEP, ResourceTypes::STONE, ResourceTypes::SHEEP};
    ResourceTypes *types2 = new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::SHEEP};
    HarvestTile tile{types1};
    HarvestTile tile2{types2};
    Player player;
    player.drawHarvestTile(tile);
    player.drawHarvestTile(tile2);
    int pos = player.placeHarvestTile(tile, 0);
    player.calculateResources(*map.getResourcedGraph(pos));
    player.resourceTracker().printScore();
    pos = player.placeHarvestTile(tile, 0);
    player.calculateResources(*map.getResourcedGraph(pos));
    player.resourceTracker().printScore();
}