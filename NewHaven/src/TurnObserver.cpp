//
// Created by hyperion on 2020-04-21.
//

#include "TurnObserver.h"
#include <iostream>
#include "GameController.h"

using namespace std;
TurnObserver::TurnObserver(){};
TurnObserver::~TurnObserver() {};
void TurnObserver::printTurnStart() {
    // At the start of a turn we should print that the player is playing a new turn
    int player_index =  GameController::current->getCurrentPlayerTurn();
    Player *current = (*GameController::current->game_settings->players)[player_index];
    // use boost to cast our int to string
    string msg = "\n" + current->getID() + " has started their turn!";
    cout << msg << endl;
}
void TurnObserver::printPlayingHarvestTile() {
    // At the start of a turn we should print that the player is playing a new turn
    int player_index =  GameController::current->getCurrentPlayerTurn();
    Player *current = (*GameController::current->game_settings->players)[player_index];
    // use boost to cast our int to string
    string msg = "\n" + current->getID() + " is playing a harvest tile!";
    cout << msg << endl;
}

void TurnObserver::printPlayedHT(){
    int player_index =  GameController::current->getCurrentPlayerTurn();
    Player *current = (*GameController::current->game_settings->players)[player_index];
    // use boost to cast our int to string
    string msg = "\n" + current->getID() + " has played a harvest tile!";
    cout << msg << endl;
    cout << "\n***UPDATED GAME BOARD CONTENT***" << endl;
    GameController::current->game_settings->board->printBoard();

}


void TurnObserver::update() {
    States gc_state = *GameController::current->game_state;
    switch(gc_state){
        case NEW_TURN:printTurnStart();break;
        case INITIAL:break;
        case SHARE_THE_WEALTH:break;
        case END_GAME:break;
        case PLAYING_HARVEST_TILE: printPlayingHarvestTile(); break;
        case PLAYED_HARVEST_TILE: printPlayedHT();break;
        case BUILDING_VILLAGE:break;
    }
}