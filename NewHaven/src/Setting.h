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
    Setting(const Setting& setting);
    Setting &operator=(const Setting& settings);
    inline int getNumberPlayers();
    inline Building* drawBuilding();
    inline HarvestTile* drawHarvestTile();
    static Setting *current;
    GBMap *board;
    vector<Player>* players;
    bool initSetting();
private:
    HarvestDeck *h_deck;
    BuildingDeck *b_deck;
    void resourceTracker();
    inline void createHarvestDeck();
    inline void createBuildingDeck();
    void setupPlayers(const int numberOfPlayers);
    void loadGameBoard(const std::string filepath);
    VGMap loadVillageMap(const std::string filepath);
    int promptNumberPlayers();
    const int *const ID_LENGTH = new const int(8);
    bool validateIDString(string id);
};


#endif //NEWHAVEN_SETUP_H
