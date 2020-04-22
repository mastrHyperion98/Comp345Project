//
// Created by hyperion on 2020-04-21.
//

#include "GameStatisticObserver.h"
#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

GameStatisticObserver::GameStatisticObserver():
        gameBoard{ new std::string },
        currentPlayer{ new std::string },
        villageBoards{ new std::vector<std::string> },
        playerBuildingCount{ new std::vector<int> },
        playerScore{ new std::vector<int> }
{}

GameStatisticObserver::GameStatisticObserver(const GameStatisticObserver& copy) :
        gameBoard{ new std::string(*copy.gameBoard) },
        villageBoards{ new std::vector<std::string>(*copy.villageBoards) },
        currentPlayer{ new std::string(*copy.currentPlayer) },
        playerBuildingCount{ new std::vector<int> },
        playerScore{new std::vector<int>(*copy.playerScore)}
{}

GameStatisticObserver& GameStatisticObserver::operator=(const GameStatisticObserver& copy)
{
    *gameBoard = *copy.gameBoard;
    *villageBoards = *copy.villageBoards;
    *currentPlayer = *copy.currentPlayer;
    *playerBuildingCount = *copy.playerBuildingCount;
    *playerScore = *copy.playerScore;

    return *this;
}

GameStatisticObserver::~GameStatisticObserver()
{
    delete gameBoard;
    delete villageBoards;
    delete currentPlayer;
    delete playerScore;
}

bool GameStatisticObserver::initialize()
{
    if (GameController::current != nullptr && GameController::current->game_settings != nullptr)
    {
        *gameBoard = GameController::current->game_settings->board->getBoardString();
        *currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayerTurn()]->getID();

        villageBoards->reserve(GameController::current->game_settings->players->size());
        playerScore->reserve(GameController::current->game_settings->players->size());

        for (std::uint_fast8_t i{ 0 }; i < GameController::current->game_settings->players->size(); ++i)
        {
            villageBoards->push_back(GameController::current->game_settings->players->operator[](i)->getVillage().getBoardString());
            playerBuildingCount->push_back(0);
            playerScore->push_back(GameController::current->game_settings->players->operator[](i)->calculateScore());
        }

        return true;
    }
    else
        throw UninitializedControllerException();

    return false;
}

void GameStatisticObserver::update() {
    States gc_state = GameController::current->getState();
    int current_player = GameController::current->getCurrentPlayerTurn();
    VG_State vg_state{NILL};
    Player * sw_player = (*GameController::current->game_settings->players)[ GameController::current->getCurrentSharePlayer()];
    Player * current = (*GameController::current->game_settings->players)[current_player];
    VG_State sw_vg_state = sw_player->getVillage().getState();

    if(current != nullptr)
        vg_state = current->getVillage().getState();

    if(gc_state==NEW_TURN){
        *currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayerTurn()]->getID();
        printCurrentPlayer();
        cout << "***YOUR VILLAGE***\n";
        printVillageBoard(*currentPlayer);
        printPlayerBuildingCount(current_player);
        printPlayerScore(current_player);
    }
    else if(gc_state==END_GAME){
        cout << "\n\nThe game has ended! Thank you for playing New Haven!" << endl;
        for(int i = 0; i < playerScore->size(); i++){
            string id = (*GameController::current->game_settings->players)[i]->getID();
            int score =  (*GameController::current->game_settings->players)[i]->calculateScore();
            cout << id << " has ended the game with " << score << " colonists!" << endl;
        }
    }
    else if(gc_state == BUILDING_VILLAGE){
        if(vg_state == BUILDING_PLAYED || vg_state == BUILDING_PLAYED_FLIPPED) {
            for (std::uint_fast8_t i{0}; i < villageBoards->size(); ++i) {
                villageBoards->operator[](i) = GameController::current->game_settings->players->operator[](
                        i)->getVillage().getBoardString();
                playerBuildingCount->operator[](i) =
                        30 - GameController::current->game_settings->players->operator[](i)->getVillage().getNumUnplayed();
                playerScore->operator[](i) = GameController::current->game_settings->players->operator[](
                        i)->calculateScore();
            }
            //printVillageBoard(*currentPlayer);
            cout << "\nREMAINING RESOURCE MARKERS" << endl;
            GameController::current->game_settings->tracker->printScore();
        }
    }
    else if(gc_state == SHARE_THE_WEALTH){
        if(sw_vg_state == BUILDING_PLAYED || sw_vg_state == BUILDING_PLAYED_FLIPPED){
            for (std::uint_fast8_t i{0}; i < villageBoards->size(); ++i) {
                villageBoards->operator[](i) = GameController::current->game_settings->players->operator[](
                        i)->getVillage().getBoardString();
                playerBuildingCount->operator[](i) =
                        30 - GameController::current->game_settings->players->operator[](i)->getVillage().getNumUnplayed();
                playerScore->operator[](i) = GameController::current->game_settings->players->operator[](
                        i)->calculateScore();
            }
            //printVillageBoard(sw_player->getID());
            cout << "\nREMAINING RESOURCE MARKERS" << endl;
            GameController::current->game_settings->tracker->printScore();
        }
    }/*
    else {
        *gameBoard = GameController::current->game_settings->board->getBoardString();
    }*/
}

void GameStatisticObserver::printGameBoard() const
{
    cout << "\n***GAME BOARD CONTENT***\n" << *gameBoard << '\n';
    cout << "\nAvailable resources:" << endl;
    GameController::current->game_settings->tracker->printScore();
    cout << "\n";
}

void GameStatisticObserver::printVillageBoard(const std::string& id) const
{
    for (size_t i = 0; i < villageBoards->size(); i++)
    {
        if (id == GameController::current->game_settings->players->operator[](i)->getID())
        {
            cout << '\n' << (*villageBoards)[i] << '\n';
            break;
        }
    }
}

void GameStatisticObserver::printCurrentPlayer() const
{
    cout << "\nCURRENT PLAYER: " << *currentPlayer << '\n';
}

void GameStatisticObserver::printPlayerBuildingCount(int& index) const
{
    cout << "\nBuildings in village: " << playerBuildingCount->operator[](index) << " buildings\n";
}


void GameStatisticObserver::printPlayerScore(int& index) const
{
    cout << "\nVillage colonists number: " << playerScore->operator[](index) << " colonists\n";
}
