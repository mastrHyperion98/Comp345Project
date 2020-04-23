//
// Created by hyperion on 2020-03-17.
// Student ID: 40057065
// Created for: Assingment 2 Concordia W2020 Comp 345 with Dr. Nora
//
// Composed of the elements required for Part 1.
//
#include "boost/lexical_cast.hpp"
#include "Setting.h"
#include "GBMapLoader.h"
#include "VGMapLoader.h"
#include "../Exceptions/InvalidConfigurationException.h"
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "iostream"

Setting::Setting():tracker{new ResourceTracker}, t_observer{new TurnObserver}, gs_observer(new GameStatisticObserver){
    h_deck = nullptr;
    b_deck = nullptr;
    board = nullptr;
    players = nullptr;

}

Setting::Setting(const Setting& setting):tracker{new ResourceTracker(*setting.tracker)},
t_observer{new TurnObserver(*setting.t_observer)},
gs_observer(new GameStatisticObserver(*setting.gs_observer))
{

    if(setting.h_deck != nullptr)
        h_deck = new HarvestDeck(*setting.h_deck);
    else
        h_deck = nullptr;
    if(setting.b_deck != nullptr)
        b_deck = new BuildingDeck(*setting.b_deck);
    else
        b_deck = nullptr;
    if(setting.board != nullptr)
        board = new GBMap(*setting.board);
    else
        board = nullptr;
    if(setting.players != nullptr)
        players = new vector<Player*>(*setting.players);
    else
        players = nullptr;
}

Setting& Setting::operator=(const Setting& setting){
    if(this == &setting)
        return *this;

    if(setting.h_deck != nullptr)
        h_deck = new HarvestDeck(*setting.h_deck);
    else
        h_deck = nullptr;
    if(setting.b_deck != nullptr)
        b_deck = new BuildingDeck(*setting.b_deck);
    else
        b_deck = nullptr;
    if(setting.board != nullptr)
        board = new GBMap(*setting.board);
    else
        board = nullptr;
    if(setting.players != nullptr)
        players = new vector<Player*>(*setting.players);
    else
        players = nullptr;

    *gs_observer = *setting.gs_observer;
   *tracker = *setting.tracker;

   return *this;
};
Setting::~Setting() {
    delete h_deck;
    delete b_deck;
    delete board;
    delete players;
    delete tracker;
    delete t_observer;
    delete gs_observer;
}
/*2
 * Setup the players, takes in the number of players and creates the proper amount.
 * Each time a player is created a prompt is asked that the player enters his/her student
 * ID number.
 */
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
        (*players)[players->size()-1]->attach(t_observer);
    }
    std::cout << numberOfPlayers << " PLAYERS HAVE BEEN SUCCESSFULLY CREATED!" << endl;
}
// validate if the ID string are only numbers
bool Setting::validateIDString(string id) {
    for(int i = 0; i < id.length(); i++){
        int ascii = id.at(i);
        if(ascii < int('0') || ascii > int('9'))
            return false;
    }
    return true;
}
// use GBMapLoader to load the proper game_board
void Setting::loadGameBoard(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    GBMapLoader loader;
    try {
        if (loader.loadConfig(filepath) && board == nullptr) {
            cout << "LOADING SUCCESSFUL" << endl;
            board = loader.generateMap();
            board->attach(tracker);
        }
    }catch(const InvalidConfigurationException &ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }catch(const BoardConfigurationNotLoaded &ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }
}
// use VGMap loader to load proper village board
VGMap Setting::loadVillageMap(const std::string filepath) {
    cout << "LOADING " << filepath << endl;
    VGMapLoader loader;
    try {
        if (loader.loadVConfig(filepath)) {
            cout << "LOADING SUCCESSFUL" << endl;
            return loader.generateVMap();
        } else
            throw BoardConfigurationNotLoaded();
    }catch(const InvalidConfigurationException &ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }catch(const BoardConfigurationNotLoaded &ex){
        cout << "LOADING FAILED" << endl;
        throw ex;
    }
}
// reset resourceTracker to default state
void Setting::resourceTracker(){
    cout << "SETTING GAME RESOURCE MARKERS!" << endl;
    tracker->reset();
    cout << "GAME RESOURCE MARKERS SET SUCCESSFULLY" << endl;
}
// User interface for inputting the number of players
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
// create the harvest deck
inline void Setting::createHarvestDeck() {
    cout << "CREATING HARVEST DECK!" << endl;
    if(h_deck == nullptr) {
        h_deck = new HarvestDeck();
        cout << "HARVEST DECK CREATED SUCCESSFULLY!" << endl;
    } else
        cout << "ERROR HARVEST DECK HAS ALREADY BEEN CREATED!";
}

// create the building deck
inline void Setting::createBuildingDeck() {
    cout << "CREATING BUILDING DECK!" << endl;
    if(b_deck == nullptr) {
        b_deck = new BuildingDeck();
        cout << "BUILDING DECK CREATED SUCCESSFULLY!" << endl;
    }
    else
        cout << "ERROR BUILDING DECK HAS ALREADY BEEN CREATED!" << endl;
}

// inline function to draw a building from the deck
inline Building* Setting::drawBuilding() {
    cout << "DRAWING A BUILDING" << endl;
    if(b_deck == nullptr)
        return nullptr;
    return b_deck->draw();
}

// inline function to draw a harvest tile from the deck
inline HarvestTile* Setting::drawHarvestTile() {
    cout << "DRAWING A HARVEST TILE" << endl;
    if(h_deck == nullptr)
        return nullptr;
    return h_deck->draw();
}

// get the number of plauyers
inline int Setting::getNumberPlayers() {
    if(players== nullptr)
        return 0;
    return players->size();
}

// main Setting loop --- initializes all the settings and make it ready for use
// returns false if failed, true otherwise.
bool Setting::initSetting() {

// define pre-processor command passed on current environment. DEBUG environment file_path is different on
// windows than Unix.
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
            (*players)[i]->setVillage(loadVillageMap(v_files[file_index]));
            (*players)[i]->attachObserverToVillage(tracker);
            (*players)[i]->attachObserverToVillage(t_observer);
            (*players)[i]->attachObserverToVillage(gs_observer);
            file_index++;
        }
        resourceTracker();
        createBuildingDeck();
        createHarvestDeck();
        for(int i = 0; i < players->size(); i++){
            cout << "NEW PLAYER GETTING READY TO DRAW HIS/HER INTIAL SETUP!" << endl;
            for (int j = 0; j < 5; j++)
                (*players)[i]->drawBuilding(drawBuilding());
            for (int j = 0; j < 2; j++)
                (*players)[i]->drawHarvestTile(drawHarvestTile());
            (*players)[i]->setShipmentTile(drawHarvestTile());

            cout << "THE NEW PLAYER HAS FINISHED DRAWING THEIR HARVEST TILES AND BUILDINGS!" << endl;
        }
    }catch(const InvalidConfigurationException &ex){
        cerr << ex.what() << endl;
        return false;
    }
    catch(const BoardConfigurationNotLoaded &ex){
        cerr << ex.what() << endl;
        return false;
    }

    gs_observer->initialize();
    return true;
}

// Slightly altered version from DrawBuilding found in Part3.5
/*
 * Iteration of user interactions to fill their hands with new buildings based on the position of the resource
 * markers
 */
void Setting::DrawBuilding(int player_index)
{
    if(player_index < 0 || player_index > players->size())
        throw std::exception();

    std::uint_fast8_t buildingCountToDraw{ 4 };

    for (std::pair<ResourceTypes, std::uint_fast16_t> const& element: tracker->getScore())
    {
        if (element.second != 0)
            buildingCountToDraw--;
    }

    // print buildings available

    bool loopPool{ true };

    for (std::uint_fast8_t i = 0; i < buildingCountToDraw; i++)
    {
        std::uint_fast16_t buildingIndex;
        char input;

        if (loopPool)
        {
            b_deck->printBuildingPool();
            std::cout << "\nEnter building card index to draw from the pool: ";

            try
            {
                std::cin >> buildingIndex;

                if (std::cin.fail() || buildingIndex <= 0 || buildingIndex > b_deck->getBuildingPoolSize())
                    throw std::exception();

                loopPool = false;
                (*players)[player_index]->drawBuildingPool(b_deck->buildingPoolDraw(buildingIndex - 1));
                continue;
            }
            catch (const std::exception&)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nThe input was invalid, please enter a valid index.\n";
                i--;
                continue;
            }
        }

        std::cout << "\nDo you want to pick another card from the pool? (y/n): ";
        try
        {
            std::cin >> input;

            if (input == 'y' || input == 'Y')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                loopPool = true;
                i--;
                continue;
            }
            else if (input == 'n' || input == 'N')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                loopPool = false;
            }
            else
            {
                throw std::exception();
            }
        }
        catch (const std::exception& e)
        {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input, try again.\n";
            i--;
            continue;
        }


        (*players)[player_index]->drawBuilding(b_deck->draw());
        //std::cout << "\nA card was drawn from the deck!" << endl;
    }

    b_deck->fillBuildingPool();
}