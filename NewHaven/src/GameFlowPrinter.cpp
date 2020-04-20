#include "GameFlowPrinter.h"
#include "GameFlowPrinter.h"
#include "GameFlowPrinter.h"
#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

GameFlowPrinter::GameFlowPrinter():
	gameBoardConfig{ new std::string },
	gameBoard{ new std::string },
	currentPlayer{ new std::string },
	villageBoards{ new std::vector<std::string> },
	playerBuildingCount{ new std::vector<int> },
	playerScore{ new std::vector<int> }
{}

GameFlowPrinter::GameFlowPrinter(const GameFlowPrinter& copy) :
	gameBoardConfig{ new std::string(*copy.gameBoardConfig) },
	gameBoard{ new std::string(*copy.gameBoard) },
	villageBoards{ new std::vector<std::string>(*copy.villageBoards) },
	currentPlayer{ new std::string(*copy.currentPlayer) },
	playerBuildingCount{ new std::vector<int> },
	playerScore{new std::vector<int>(*copy.playerScore)}
{}

GameFlowPrinter& GameFlowPrinter::operator=(const GameFlowPrinter& copy)
{
	*gameBoardConfig = *copy.gameBoardConfig;
	*gameBoard = *copy.gameBoard;
	*villageBoards = *copy.villageBoards;
	*currentPlayer = *copy.currentPlayer;
	*playerBuildingCount = *copy.playerBuildingCount;
	*playerScore = *copy.playerScore;

	return *this;
}

GameFlowPrinter::~GameFlowPrinter()
{
	delete gameBoardConfig;
	delete gameBoard;
	delete villageBoards;
	delete currentPlayer;
	delete playerScore;
}

bool GameFlowPrinter::initialize()
{
	if (GameController::current != nullptr && GameController::current->game_settings != nullptr)
	{
		*gameBoardConfig = GameController::current->game_settings->board->printIndexConfiguration();
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

void GameFlowPrinter::update() {

    if ((*GameController::current->controller_status)["new_turn"])
        printNewTurn();
    else if ((*GameController::current->controller_status)["start_turn"]) {
        int play_turn{GameController::current->getCurrentPlayerTurn()};
        printGameBoardConfig();
        printGameBoard();
        cout << "Here are your building cards:\n";
        (*GameController::current->game_settings->players)[play_turn]->printBuildingCards();
        cout << "\nHere are your Harvest Tiles:\n";
        (*GameController::current->game_settings->players)[play_turn]->printHarvestCards();
    }
    else if (GameController::current->game_settings->board->RT != nullptr){
        *gameBoard = GameController::current->game_settings->board->getBoardString();
        printGameBoard();
    }
    else if((*GameController::current->controller_status)["begin_sw"]){
    }
    else {
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
}

void GameFlowPrinter::printGameBoardConfig()
{
	cout << "\n***GAME BOARD ID CONFIGURATION***\n" << *gameBoardConfig << '\n';
}

void GameFlowPrinter::printGameBoard() const
{
	cout << "\n***GAME BOARD CONTENT***\n" << *gameBoard << '\n';
	cout << "\nAvailable resources:" << endl;
    GameController::current->game_settings->tracker->printScore();
    cout << "\n";
}

void GameFlowPrinter::printVillageBoard(const std::string& id) const
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

void GameFlowPrinter::printCurrentPlayer() const
{
	cout << "\nCURRENT PLAYER: " << *currentPlayer << '\n';
}

void GameFlowPrinter::printPlayerBuildingCount(int& index) const
{
	cout << "\nBuildings in village: " << playerBuildingCount->operator[](index) << " buildings\n";
}


void GameFlowPrinter::printPlayerScore(int& index) const
{
	cout << "\nVillage colonists number: " << playerScore->operator[](index) << " colonits\n";
}

void GameFlowPrinter::printNewTurn() const {
    printCurrentPlayer();
    int play_turn{GameController::current->getCurrentPlayerTurn()};
    printPlayerBuildingCount(play_turn);
    printPlayerScore(play_turn);
}