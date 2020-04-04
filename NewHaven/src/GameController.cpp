//
// Created by Steven Smith(aka hyperion --> github alias) on 2020-03-27.
// Student ID: 40057065
// Created for: Assingment 2 Concordia W2020 Comp 345 with Dr. Nora
//
// GameController controls the environment and the main game loop of NewHaven
// It uses a singleton design such that essential components such as game decks
// can be assessed anywhere through maintaining only a single instance of GameController.
// Is composed of an aglomeration of functions defined in part 3 and modified to fit the need or
// refactored when the quality of the code was inadequate.

#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
// singleton instance
GameController* GameController::current;
// default constructor
GameController::GameController():current_turn_player{new int(0)}, game_settings{nullptr}{
    // singleton only one instance allowed
    delete current;
    current = this;
}
// parametrized constructor
GameController::GameController(const GameController& controller):
current_turn_player{new int(*controller.current_turn_player)},  game_settings{nullptr}{
    delete current;
    current = this;
}
// assignment operator overlaod
GameController& GameController::operator=(const GameController &controller) {
    if(this == &controller)
        return *this;
    *current_turn_player = *controller.current_turn_player;
    if(game_settings == nullptr && controller.game_settings != nullptr)
        game_settings=new Setting(*controller.game_settings);
    else if(game_settings != nullptr && controller.game_settings != nullptr)
        *game_settings = *controller.game_settings;

    return *this;
}
// destructor
GameController::~GameController(){
    delete game_settings;
    delete current_turn_player;
    current = nullptr;
}
// start
// //contains the main loop
void GameController::start(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();
    for(int i = 0; i < 25; i++){
        cout << "\n"; // clear screen
    }
    cout << "STARTING PLAYER HAS ID: " << (*game_settings->players)[*current_turn_player]->getID() << endl;
    while(!hasGameEnded()){
        // PrintGameBoard
        playTurn();
        *current_turn_player = ((*current_turn_player)+1) % game_settings->players->size();
    }

    endGame();
}
// initialize the gameController such that all settings are configured properly
bool GameController::initialize() {
    game_settings = new Setting();
    bool init = game_settings->initSetting();
    if(init)
        *current_turn_player = startingPlayer();
    return init;
}
// find the starting player by comparing their studentID
int GameController::startingPlayer() {
int current_index = 0;
for(int i = 0; i < game_settings->players->size(); i++){
    try {
        int current_id = boost::lexical_cast<int>((*game_settings->players)[current_index]->getID());
        int next_id = boost::lexical_cast<int>((*game_settings->players)[i]->getID());
        if(next_id < current_id)
            current_index = i;
    }
    catch (std::exception &e) {
        cout << "ERROR COULD NOT DETERMINE STARTING PLAYER! ERROR IN STRING-INT CAST ID NOT NUMERIC" << endl;
       // terminate application
        exit(-1);
    }
    }
    return current_index;
}
//  playTurn function that executes the turn of the current player and all the user
// interaction needed to complete it
void GameController::playTurn(){
    int pos{-1};
    bool shipmentPlayed{false};
    if(game_settings == nullptr)
        throw UninitializedControllerException();
    // Print board ID configuration
    cout << "***GAME BOARD ID CONFIGURATION***" << endl;
    game_settings->board->printIndexConfiguration();
    cout << endl;
    cout << "***GAME BOARD CONTENT***" << endl;
    game_settings->board->printBoard();
    cout << endl;
    cout << (*game_settings->players)[*current_turn_player]->getID() << " Your turn! What would you like to do? "
            "Enter the number for the move you'd like to make." << endl;

    Player *current = (*game_settings->players)[*current_turn_player];
    int tile_option = selectTileOption();
    if(tile_option == 1) {
        pos=current->placeHarvestTile();
        ResourceTrails *trail = game_settings->board->getResourcedGraph(pos);
        game_settings->tracker->computeScore(*trail);
    }
        // play the shipmentTile
    else if(tile_option == 2){
        pos = playShipmentTile(selectResourceType(), current);
        shipmentPlayed = true;
    }

    cout << "***UPDATED GAME BOARD CONTENT***" << endl;
    game_settings->board->printBoard();
    // current player builds his village
    current->buildVillage();
    shareTheWealth();
    game_settings->DrawBuilding(*current_turn_player);

    if(shipmentPlayed){
        delete game_settings->board->getHarvestTile(pos)->tileContent;
        game_settings->board->getHarvestTile(pos)->tileContent = original_shipment;
        shipmentPlayed = false;
    }
    else{
        // draw a harvest tile only if one from the players hand was consumed.
        current->drawHarvestTile(game_settings->drawHarvestTile());
    }
}
// end game function
void GameController::endGame(){
// requires part4 and isnt part of what is needed for Part 2 driver
}

// Restart the game
void GameController::restart(){
    delete game_settings;
    initialize();
    start();
}
bool GameController::hasGameEnded(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();
    // return isGameBoard has only 1 tile left
    // requires a function defined in part 4.
    return false;
}
inline int GameController::selectTileOption() {
    int choice;
    std::string prompt = "1\tPlay a Harvest tile from your possession"
                         "\n2\tPlay with your Shipment tile."
                         "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2
            || (choice == 2 && (*game_settings->players)[*current_turn_player]->getShipmentTile() == nullptr)){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }
    return choice;
}

inline ResourceTypes GameController::selectResourceType() {
    int choice;
    std::string prompt =  "Which resource type would you like?"
                                  "\n\t1 - Sheep"
                                  "\n\t2 - Stone"
                                  "\n\t3 - Wood\n"
                                  "\t4 - Wheat"
                                  "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 4){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }
    ResourceTypes type;
    if(choice == 1)
        type = ResourceTypes::SHEEP;
    else if(choice == 2)
        type= ResourceTypes::STONE;
    else if(choice == 3)
        type = ResourceTypes::WOOD;
    else
        type = ResourceTypes::WHEAT;
    return type;
}
inline void GameController::setOriginalShipmentTile(Player *player){
    original_shipment = player->getShipmentTile()->tileContent;
}
int GameController::playShipmentTile(ResourceTypes type, Player *player){
    ResourceTypes *tmp_res{new ResourceTypes[4]{type,type,type,type}};
    setOriginalShipmentTile(player);
    // player plays the shipment tile.
    player->getShipmentTile()->tileContent = tmp_res;
    int pos{0};
    POSITION:
    while((cout <<  "position index to place tile: " && !( cin >> pos)) || pos < 0
          || pos >= (25 + (10 * *game_settings->board->CONFIG))){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile index" << endl;
    }
    // later this will be called from the singleton Game Controller
    if(game_settings->board!= nullptr) {
        if(game_settings->board->placeHarvestTile(pos, player->getShipmentTile())){
            // print new board config
            player->setShipmentPlayed();
            // compute resourceTracker using compies
            game_settings->tracker->computeScore(*game_settings->board->getResourcedGraph(pos));
            // once resource_score is calculated we flip the tile over
        } else{
            cout << "Position Index is invalid. It has already been played!"<<endl;
            goto POSITION;
        }
    }
    return pos;
}
/*
 * Share the wealth function. We decided to alter the structure of the player slighty and
 * move the resourceTracker object off the players. It is dependent solely on the resourceTrail generated by
 * the game board. As such maintaining up to four instance of the object (1 per player) seemed inefficient
 * and a waste of space. A single resourceTracker facility exists within the Settings file (Part 1)
 * and is used to service all the players. We believe this to be much more efficient.
 *
 * This has been changed as the A1 requirements vaguely talked about a resourceTracker() held by the
 * player. This was poorly described and lack any indication as to its usage within the player class.
 */
void GameController::shareTheWealth(){
    int player_index{static_cast<int>((*current_turn_player + 1) % game_settings->players->size())};
    do{
        // print out the available resources
        // prompt user to action
        string prompt = (*game_settings->players)[player_index]->getID() + " Would you like to use the leftover resources to erect a building in your village?"
                        "\n1\tErect a building.\n2\tPass\nChoice: ";
        int choice{0};
        while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2){
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "This is not a valid move. Select either 1 or 2:" << endl;
        }
        // call build village for that user
        if(choice == 1){
            (*game_settings->players)[player_index]->buildVillage();
        }

        cout << "Leftover resources:" << endl;
        game_settings->tracker->printScore();

        player_index = ++player_index % game_settings->players->size();

    }while(player_index != *current_turn_player && !game_settings->tracker->isEmpty());
}

