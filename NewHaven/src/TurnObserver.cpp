//
// Created by hyperion on 2020-04-21.
//

#include "TurnObserver.h"
#include <iostream>
#include "GameController.h"

using namespace std;
TurnObserver::TurnObserver(){};
TurnObserver::~TurnObserver() {
    delete current;
};
void TurnObserver::printTurnStart() {
    // At the start of a turn we should print that the player is playing a new turn
    int player_index =  GameController::current->getCurrentPlayerTurn();
    delete current;
    current = (*GameController::current->game_settings->players)[player_index];

    // use boost to cast our int to string
    string msg = "\n" + current->getID() + " has started their turn!";
    cout << msg << endl;
}
void TurnObserver::printPlayingHarvestTile() {

    string msg = "\n" + current->getID() + " is playing a harvest tile!";
    cout << msg << endl;
}

void TurnObserver::printPlayedHT(){
    string msg = "\n" + current->getID() + " has played a harvest tile!";
    cout << msg << endl;
    cout << "\n***UPDATED GAME BOARD CONTENT***" << endl;
    GameController::current->game_settings->board->printBoard();
    cout << "The resource marker has increased!" << endl;
    GameController::current->game_settings->tracker->printScore();
}


void TurnObserver::printBV() {
    string msg = "\n" + current->getID() + " is building their village!";
    cout << msg << endl;
}

void TurnObserver::printSW() {
    Player * sw_player = (*GameController::current->game_settings->players)[ GameController::current->getCurrentSharePlayer()];
    string msg = "\n" + current->getID() + " is sharing their wealth with " + sw_player->getID();
    cout << msg << endl;
}
void TurnObserver::printBuildingPlayed(bool flipped){
    if(flipped)
       cout << "\n" + current->getID() << " has played a building of type " <<
                current->getVillage().last_played->building->getBuildingType() << " flipped at position "
                << *current->getVillage().last_played->position
                << "\n"  <<  *current->getVillage().last_played->vCost << " "
                << current->getVillage().last_played->building->getBuildingType() << " has been consumed!"
                << endl;
    else
        cout << "\n" + current->getID() << " has played a building of type " <<
             current->getVillage().last_played->building->getBuildingType() << " at position "
             << *current->getVillage().last_played->position
             << "\n"  <<  *current->getVillage().last_played->vCost << " "
             << current->getVillage().last_played->building->getBuildingType() << " has been consumed and removed from the resource tracker!"
             << endl;

}
void TurnObserver::printBuildingPlayedSW(bool flipped){

    Player * sw_player = (*GameController::current->game_settings->players)[ GameController::current->getCurrentSharePlayer()];
    if(flipped)
        cout << "\n" + sw_player->getID() << " has played a building of type " <<
        sw_player->getVillage().last_played->building->getBuildingType() << " flipped at position "
             << *sw_player->getVillage().last_played->position
             << "\n"  <<  *sw_player->getVillage().last_played->vCost << " "
             << sw_player->getVillage().last_played->building->getBuildingType() << " has been consumed!"
             << endl;
    else
        cout << "\n" + sw_player->getID() << " has played a building of type " <<
        sw_player->getVillage().last_played->building->getBuildingType() << " at position "
             << *sw_player->getVillage().last_played->position
             << "\n"  <<  *sw_player->getVillage().last_played->vCost << " "
             << sw_player->getVillage().last_played->building->getBuildingType() << " has been consumed and removed from the resource tracker!"
             << endl;

}

void TurnObserver::printEndTurn() {
    string msg = "\n" + current->getID() + " has ended their turn!";
    cout << msg << endl;
}
void TurnObserver::update() {
    States gc_state = GameController::current->getState();
    VG_State vg_state{NILL};
    Player * sw_player = (*GameController::current->game_settings->players)[ GameController::current->getCurrentSharePlayer()];
    VG_State sw_vg_state{sw_player->getVillage().getState()};
    if(current != nullptr)
        vg_state = current->getVillage().getState();
    switch(gc_state){
        case NEW_TURN:printTurnStart();break;
        case INITIAL:break;
        case SHARE_THE_WEALTH:
            // condition based on Player state
            if(sw_vg_state == BUILDING_PLAYED_FLIPPED)
                printBuildingPlayedSW(true);
            else if(sw_vg_state == BUILDING_PLAYED)
                printBuildingPlayedSW(false);
            else
                printSW();
            break;
        case END_GAME:break;
        case END_TURN: printEndTurn();break;
        case PLAYING_HARVEST_TILE: printPlayingHarvestTile(); break;
        case PLAYED_HARVEST_TILE: printPlayedHT();break;
        case BUILDING_VILLAGE:
            // condition based on Player state
            if(vg_state == BUILDING_PLAYED_FLIPPED)
                printBuildingPlayed(true);
            else if(vg_state == BUILDING_PLAYED)
                printBuildingPlayed(false);
            else
                 printBV();

            break;
    }
}