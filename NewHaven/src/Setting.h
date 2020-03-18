//
// Created by hyperion on 2020-03-17.
//

#ifndef NEWHAVEN_SETUP_H
#define NEWHAVEN_SETUP_H
#include <vector>
#include "Player.h"
#include "GBMap.h"
#include <string>
class Setting {
public:
    Setting();
    ~Setting();
    static void setupPlayers(const int numberOfPlayers);
    static void loadGameBoard(const std::string filepath);
    static void loadVillageMap(const std::string filepath);
    static void ResourceTracker();
    int promptNumberPlayers();
    static void createHarvestDeck();
    static void createBuildingDeck();
    static Building& DrawBuilding();
    static HarvestTile& DrawHarvestTile();
    static HarvestDeck *h_deck;
    static BuildingDeck *b_deck;
    static GBMap *board;
    static vector<Player> *players;
};


#endif //NEWHAVEN_SETUP_H
