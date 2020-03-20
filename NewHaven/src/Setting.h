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
    inline static int getNumberPlayers();
    inline static Building* drawBuilding();
    inline static HarvestTile* drawHarvestTile();
    static GBMap *board;
    static vector<Player>* players;
private:
    static HarvestDeck *h_deck;
    static BuildingDeck *b_deck;
    static void resourceTracker();
    inline static void createHarvestDeck();
    inline static void createBuildingDeck();
    static void setupPlayers(const int numberOfPlayers);
    static void loadGameBoard(const std::string filepath);
    static VGMap loadVillageMap(const std::string filepath);
    int promptNumberPlayers();
};


#endif //NEWHAVEN_SETUP_H
