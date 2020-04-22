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
        *gameBoard = GameController::current->game_settings->board->getBoardString();
        *currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayerTurn()]->getID();
        for (std::uint_fast8_t i{0}; i < villageBoards->size(); ++i) {
            villageBoards->operator[](i) = GameController::current->game_settings->players->operator[](
                    i)->getVillage().getBoardString();
            playerBuildingCount->operator[](i) =
                    30 - GameController::current->game_settings->players->operator[](i)->getVillage().getNumUnplayed();
            playerScore->operator[](i) = GameController::current->game_settings->players->operator[](
                    i)->calculateScore();
        }
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
    cout << "\nVillage colonists number: " << playerScore->operator[](index) << " colonits\n";
}
