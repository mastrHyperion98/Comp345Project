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
    static VGMap loadVillageMap(const std::string filepath);
    static void resourceTracker();
    int promptNumberPlayers();
    inline static void createHarvestDeck();
    inline static void createBuildingDeck();
    inline static Building* drawBuilding();
    inline static HarvestTile* drawHarvestTile();
    static HarvestDeck *h_deck;
    static BuildingDeck *b_deck;
    static GBMap *board;
    static vector<Player> *players;
};


#endif //NEWHAVEN_SETUP_H
