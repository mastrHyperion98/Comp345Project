//
// Created by hyperion on 2020-03-27.
//

#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
GameController::GameController():current_turn_player{new int(0)}, game_settings{nullptr}{
}

GameController::GameController(const GameController& controller):
current_turn_player{new int(*controller.current_turn_player)},  game_settings{nullptr}{
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
}

void GameController::start(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();

    while(!hasGameEnded()){
        // PrintGameBoard
        playTurn();
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
    int tile_option = selectTileOption();
    Player *current = (*game_settings->players)[*current_turn_player];
    /**TO-DO
     * Player Turn
     * Share The Wealth
     */
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

inline int GameController::selectTileOption() {
    int choice;
    std::string prompt = "1\tPlay a Harvest tile from your possession"
                         "\n2\tPlay with your Shipment tile."
                         "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }

    return choice;
}