//
// Created by hyperion on 2020-03-17.
//
#include "Setting.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "../Exceptions/InvalidConfigurationException.h"
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "iostream"

Setting* Setting::current;

Setting::Setting(){
    h_deck = nullptr;
    b_deck = nullptr;
    board = nullptr;
    players = nullptr;
    delete current;
    current = this;
}

Setting::Setting(const Setting& setting):h_deck{new HarvestDeck(*setting.h_deck)}, b_deck{new BuildingDeck(*setting.b_deck)},
    board{new GBMap(*setting.board)}, players{new vector<Player>(*setting.players)}{
    // singleton design we dont need any other reference but the current one
    delete current;
    current = this;
}

Setting& Setting::operator=(const Setting& setting){
    if(this == &setting)
        return *this;

   if(setting.h_deck != nullptr)
    h_deck = new HarvestDeck(*setting.h_deck);
   if(setting.b_deck != nullptr)
    b_deck = new BuildingDeck(*setting.b_deck);
   if(setting.board != nullptr)
    board = new GBMap(*setting.board);
   if(setting.players != nullptr)
    players = new vector<Player>(*setting.players);
    current = this;
    return *this;
};
Setting::~Setting() {
    delete h_deck;
    delete b_deck;
    delete board;
    delete players;
    current = nullptr;
}

void Setting::setupPlayers(const int numberOfPlayers) {
    std::cout << "CREATING " << numberOfPlayers << " PLAYERS!" << endl;
    if(players == nullptr)
        players = new vector<Player>;
    players->clear();
    for(int i = 0; i < numberOfPlayers;i++){
        players->push_back(Player());
    }
    std::cout << numberOfPlayers << " PLAYERS HAVE BEEN SUCCESSFULLY CREATED!" << endl;
}

void Setting::loadGameBoard(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    GBMapLoader loader;
    if(loader.loadConfig(filepath) && board == nullptr) {
        cout << "LOADING SUCCESSFUL" << endl;
        board = loader.generateMap();
    }
    else{
    cout << "LOADING FAILED! AN ERROR HAS OCCURRED" << endl;
    throw BoardConfigurationNotLoaded();
    }
}

VGMap Setting::loadVillageMap(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    VGMapLoader loader;
    if(loader.loadVConfig(filepath)) {
        cout << "LOADING SUCCESSFUL" << endl;
        return loader.generateVMap();
    }
    cout << "LOADING FAILED! AN ERROR HAS OCCURRED" << endl;
    throw InvalidConfigurationException();
}

void Setting::resourceTracker(){
    cout << "SETTING GAME RESOURCE MARKERS!" << endl;
    for(std::vector<Player>::iterator it = players->begin() ; it != players->end(); ++it){
        it->resourceTracker()->score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WHEAT,0));
        it->resourceTracker()->score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::STONE,0));
        it->resourceTracker()->score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::SHEEP,0));
        it->resourceTracker()->score->insert(pair<ResourceTypes,std::uint_least16_t>(ResourceTypes::WOOD,0));
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
    if(h_deck == nullptr) {
        h_deck = new HarvestDeck();
        cout << "HARVEST DECK CREATED SUCCESSFULLY!" << endl;
    } else
        cout << "ERROR HARVEST DECK HAS ALREADY BEEN CREATED!";
}

inline void Setting::createBuildingDeck() {
    cout << "CREATING BUILDING DECK!" << endl;
    if(b_deck == nullptr) {
        b_deck = new BuildingDeck();
        cout << "BUILDING DECK CREATED SUCCESSFULLY!" << endl;
    }
    else
        cout << "ERROR BUILDING DECK HAS ALREADY BEEN CREATED!" << endl;
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

void Setting::initSetting() {
    string files[3] = {"../config/GBMapConfig_0.config",
                       "../config/GBMapConfig_1.config",
                       "../config/GBMapConfig_2.config" };

    string v_files[4] = {"../config/VGMapNum_0.config",
                         "../config/VGMapNum_1.config",
                         "../config/VGMapNum_2.config",
                         "../config/VGMapNum_3.config"
    };
    int number_players{promptNumberPlayers()};
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
    int file_index = 0;
    for(std::vector<Player>::iterator it = players->begin(); it != players->end(); ++it){
        it->setVillage(loadVillageMap(v_files[file_index]));
        file_index++;
    }
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