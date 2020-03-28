//
// Created by hyperion on 2020-03-27.
//

#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

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

void GameController::playTurn(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();

    /**TO-DO
     * Player Turn
     * Share The Wealth
     */
}

void GameController::endGame(){

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
}