//
// Created by hyperion on 2020-03-17.
//
#include "Setting.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "iostream"
HarvestDeck* Setting::h_deck;
BuildingDeck* Setting::b_deck;
GBMap* Setting::board;
vector<Player>* Setting::players;

Setting::Setting(){
    h_deck = nullptr;
    b_deck = nullptr;
    board = nullptr;
    players = new vector<Player>;
}

Setting::~Setting() {
    delete h_deck;
    delete b_deck;
    delete board;
    delete players;
}

void Setting::setupPlayers(const int numberOfPlayers) {
    std::cout << "CREATING " << numberOfPlayers << " PLAYERS!" << endl;
    players->clear();
    for(int i = 0; i < numberOfPlayers;i++){
        Player *player = new Player();
        players->push_back(*player);
    }
    std::cout << numberOfPlayers << " PLAYERS HAVE BEEN SUCCESSFULLY CREATED!" << endl;
}

void Setting::loadGameBoard(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    GBMapLoader loader;
    if(loader.loadConfig(filepath)) {
        cout << "LOADING SUCCESSFUL" << endl;
        board = loader.generateMap();
    }
    else
    cout << "LOADING FAILED! AN ERROR HAS OCCURRED" << endl;
}

VGMap Setting::loadVillageMap(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    VGMapLoader loader;
    if(loader.loadVConfig(filepath)) {
        cout << "LOADING SUCCESSFUL" << endl;
        VGMap map = loader.generateVMap();
    }
    cout << "LOADING FAILED! AN ERROR HAS OCCURRED" << endl;
}

void Setting::resourceTracker(){
    cout << "SETTING GAME RESOURCE MARKERS!" << endl;
    for(std::vector<Player>::iterator it = players->begin() ; it != players->end(); ++it){
        it->resourceTracker().score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WHEAT,0));
        it->resourceTracker().score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::STONE,0));
        it->resourceTracker().score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::SHEEP,0));
        it->resourceTracker().score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WOOD,0));
    }
    cout << "GAME RESOURCE MARKERS SET SUCCESSFULLY" << endl;
}

int Setting::promptNumberPlayers() {
    int number_of_players;
    while ((cout << "Enter the number of players (2, 3 or 4): " && !(cin >> number_of_players))
    || number_of_players < 2 || number_of_players >4) {
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    return number_of_players;
}

inline void Setting::createHarvestDeck() {
    cout << "CREATING HARVEST DECK!" << endl;
    h_deck = new HarvestDeck();
    cout << "HARVEST DECK CREATED SUCCESFULLY!" << endl;
}

inline void Setting::createBuildingDeck() {
    cout << "CREATING BUILDING DECK!" << endl;
    b_deck = new BuildingDeck();
    cout << "BUILDING DECK CREATED SUCCESFULLY!" << endl;
}

inline Building* Setting::drawBuilding() {
    cout << "DRAWING A BUILDING" << endl;
    if(b_deck == nullptr)
        return nullptr;
    return b_deck->draw();
}

inline HarvestTile* Setting::drawHarvestTile() {
    cout << "DRAWING A HARVEST TILE" << endl;
    if(h_deck == nullptr)
        return nullptr;
    return h_deck->draw();
}

inline int Setting::getNumberPlayers() {
    if(players== nullptr)
        return 0;
    return players->size();
}

bool Setting::initSetting() {
    string files[3] = {"../config/GBMapConfig_0.config",
                       "../config/GBMapConfig_1.config",
                       "../config/GBMapConfig_2.config" };
    int number_players = promptNumberPlayers();
    switch(number_players){
        case 2:
            loadGameBoard(files[0]);break;
        case 3:
            loadGameBoard(files[1]);break;
        case 4:
            loadGameBoard(files[2]);break;
        default:
            loadGameBoard(files[0]);break;
    }
    setupPlayers(number_players);
    resourceTracker();
    createBuildingDeck();
    createHarvestDeck();
    for(std::vector<Player>::iterator it = players->begin() ; it != players->end(); ++it){
        cout << "NEW PLAYER GETTING READY TO DRAW HIS/HER INTIAL SETUP!" << endl;
        for(int i = 0; i < 5; i++)
             it->drawBuilding(drawBuilding());
        for(int j = 0; j < 2; j++)
            it->drawHarvestTile(drawHarvestTile());
        it->setShipmentTile(drawHarvestTile());

        cout << "THE NEW PLAYER HAS FINISHED DRAWING THEIR HARVEST TILES AND BUILDINGS!" << endl;
    }
}