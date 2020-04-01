//
// Created by hyperion on 2020-03-17.
//
#include "boost/lexical_cast.hpp"
#include "Setting.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "../Exceptions/InvalidConfigurationException.h"
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "iostream"

Setting* Setting::current;

Setting::Setting():tracker{new ResourceTracker}{
    h_deck = nullptr;
    b_deck = nullptr;
    board = nullptr;
    players = nullptr;
    delete current;
    current = this;

}

Setting::Setting(const Setting& setting):h_deck{new HarvestDeck(*setting.h_deck)}, b_deck{new BuildingDeck(*setting.b_deck)},
    board{new GBMap(*setting.board)}, players{new vector<Player*>(*setting.players)}, tracker{new ResourceTracker{*setting.resourceTracker()};}{
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
    players = new vector<Player*>(*setting.players);

   *tracker = *setting.tracker;
    current = this;
    return *this;
};
Setting::~Setting() {
    delete h_deck;
    delete b_deck;
    delete board;
    delete players;
    delete tracker;
    current = nullptr;
}

void Setting::setupPlayers(const int numberOfPlayers) {
    std::cout << "CREATING " << numberOfPlayers << " PLAYERS!" << endl;
    if(players == nullptr)
        players = new vector<Player*>;
    players->clear();
    for(int i = 0; i < numberOfPlayers;i++){
        string id{""};
        while ((cout << "Enter your 8-digit student ID number: " && !(cin >> id))
               || id.length() != *ID_LENGTH || !validateIDString(id)) {
            id.clear();
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Invalid input; please re-enter.\n";
        }
        players->push_back(new Player(id));
    }
    std::cout << numberOfPlayers << " PLAYERS HAVE BEEN SUCCESSFULLY CREATED!" << endl;
}
bool Setting::validateIDString(string id) {
    for(int i = 0; i < id.length(); i++){
        int ascii = id.at(i);
        if(ascii < int('0') || ascii > int('9'))
            return false;
    }
    return true;
}
void Setting::loadGameBoard(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    GBMapLoader loader;
    try {
        if (loader.loadConfig(filepath) && board == nullptr) {
            cout << "LOADING SUCCESSFUL" << endl;
            board = loader.generateMap();
        }
    }catch(InvalidConfigurationException ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }catch(BoardConfigurationNotLoaded ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }
}

VGMap Setting::loadVillageMap(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    VGMapLoader loader;
    try {
        if (loader.loadVConfig(filepath)) {
            cout << "LOADING SUCCESSFUL" << endl;
            return loader.generateVMap();
        }
    }catch(InvalidConfigurationException ex){
        cout << "LOADING FAILED" << endl;
        throw InvalidConfigurationException();
    }catch(BoardConfigurationNotLoaded ex){
        cout << "LOADING FAILED" << endl;
        throw BoardConfigurationNotLoaded();
    }
}

void Setting::resourceTracker(){
    cout << "SETTING GAME RESOURCE MARKERS!" << endl;
    tracker->reset();
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

bool Setting::initSetting() {


#ifdef _DEBUG
    string files[3] = {"../../../config/GBMapConfig_0.config",
                       "../../../config/GBMapConfig_1.config",
                       "../../../config/GBMapConfig_2.config" };

    string v_files[4] = {"../../../config/VGMapNum_0.config",
                         "../../../config/VGMapNum_1.config",
                         "../../../config/VGMapNum_2.config",
                         "../../../config/VGMapNum_3.config"
    };
#else
    string files[3] = {"../config/GBMapConfig_0.config",
                       "../config/GBMapConfig_1.config",
                       "../config/GBMapConfig_2.config" };

    string v_files[4] = {"../config/VGMapNum_0.config",
                         "../config/VGMapNum_1.config",
                         "../config/VGMapNum_2.config",
                         "../config/VGMapNum_3.config"
    };
#endif // DEBUG

    int number_players{promptNumberPlayers()};
    try {
        switch (number_players) {
            case 2:
                loadGameBoard(files[0]);
                break;
            case 3:
                loadGameBoard(files[1]);
                break;
            case 4:
                loadGameBoard(files[2]);
                break;
            default:
                loadGameBoard(files[0]);
                break;
        }
        setupPlayers(number_players);
        int file_index = 0;
        for(int i = 0; i < players->size(); i++){
            Player* it = (*players)[i];
            it->setVillage(loadVillageMap(v_files[file_index]));
            file_index++;
        }
        resourceTracker();
        createBuildingDeck();
        createHarvestDeck();
        for(int i = 0; i < players->size(); i++){
            Player* it = (*players)[i];
            cout << "NEW PLAYER GETTING READY TO DRAW HIS/HER INTIAL SETUP!" << endl;
            for (int i = 0; i < 5; i++)
                it->drawBuilding(drawBuilding());
            for (int j = 0; j < 2; j++)
                it->drawHarvestTile(drawHarvestTile());
            it->setShipmentTile(drawHarvestTile());

            cout << "THE NEW PLAYER HAS FINISHED DRAWING THEIR HARVEST TILES AND BUILDINGS!" << endl;
        }
    }catch(InvalidConfigurationException ex){
        cerr << ex.what() << endl;
        return false;
    }
    catch(BoardConfigurationNotLoaded ex){
        cerr << ex.what() << endl;
        return false;
    }
    return true;
}

