//
// Created by hyperion on 2020-03-27.
//

#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>

GameController* GameController::current;
GameController::GameController():current_turn_player{new int(0)}, game_settings{nullptr}{
    // singleton only one instance allowed
    delete current;
    current = this;
}

GameController::GameController(const GameController& controller):
current_turn_player{new int(*controller.current_turn_player)},  game_settings{nullptr}{
    delete current;
    current = this;
}

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

GameController::~GameController(){
    delete game_settings;
    delete current_turn_player;
    current = nullptr;
}

void GameController::start(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();
    for(int i = 0; i < 100; i++){
        cout << "\n"; // clear screen
    }
    while(!hasGameEnded()){
        // PrintGameBoard
        playTurn();
        *current_turn_player = *current_turn_player % game_settings->players->size();
    }

    endGame();
}
// initialize the gameController
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
        /**
         * TO-DO: REPLACE WITH A PROPER EXCEPTION TO BE CAUGHT BY THE DRIVER
         */
        cout << "ERROR COULD NOT DETERMINE STARTING PLAYER! ERROR IN STRING-INT CAST ID NOT NUMERIC" << endl;
       // terminate application
        exit(-1);
    }
    }
    return current_index;
}
void GameController::playTurn(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();

    cout << "Your turn! What would you like to do? "
            "Enter the number for the move you'd like to make." << endl;

    Player *current = (*game_settings->players)[*current_turn_player];
    int tile_option = selectTileOption(current->isShipmentPlayed());
    if(tile_option == 1) {
        int pos{current->placeHarvestTile()};
        ResourceTrails *trail = game_settings->board->getResourcedGraph(pos);
        game_settings->tracker->computeScore(*trail);
    }
        // play the shipmentTile
    else if(tile_option == 2)
        playShipmentTile(selectResourceType(), current);

    cout << "Available resources:" << endl;
    game_settings->tracker->printScore();
    current->buildVillage();
    shareTheWealth();
    game_settings->DrawBuilding(*current_turn_player);

}

void GameController::endGame(){
// requires part4
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
    return false;
}

inline int GameController::selectTileOption(bool shipmentPlayed) {
    int choice;
    std::string prompt = "1\tPlay a Harvest tile from your possession"
                         "\n2\tPlay with your Shipment tile."
                         "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2
            || (choice == 2 &&shipmentPlayed)){
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
void GameController::playShipmentTile(ResourceTypes type, Player *player){
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
            player->getShipmentTile()->tileContent=original_shipment;
            original_shipment = nullptr;
        } else{
            cout << "Position Index is invalid. It has already been played!"<<endl;
            goto POSITION;
        }
    }
}

void GameController::shareTheWealth(){
    int player_index{static_cast<int>((*current_turn_player + 1) % game_settings->players->size())};
    do{
        // print out the available resources
        cout << "Available resources:" << endl;
        game_settings->tracker->printScore();
        // prompt user to action
        string prompt = "Would you like to use the leftover resources to erect a building in your village?"
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

    }while(player_index != *current_turn_player || !game_settings->tracker->isEmpty());
}

