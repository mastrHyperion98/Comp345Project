#include "GameFlowPrinter.h"
#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

GameFlowPrinter::GameFlowPrinter():
	gameBoardConfig{ new std::string },
	gameBoard{ new std::string },
	villageBoards{ new std::vector<std::string> },
	currentPlayer{ new std::string }
{}

GameFlowPrinter::GameFlowPrinter(const GameFlowPrinter& copy) :
	gameBoardConfig{ new std::string(*copy.gameBoardConfig) },
	gameBoard{ new std::string(*copy.gameBoard) },
	villageBoards{ new std::vector<std::string>(*copy.villageBoards) },
	currentPlayer{ new std::string(*copy.currentPlayer) }
{}

GameFlowPrinter& GameFlowPrinter::operator=(const GameFlowPrinter& copy)
{
	*gameBoard = *copy.gameBoard;
	*villageBoards = *copy.villageBoards;
	*currentPlayer = *copy.currentPlayer;

	return *this;
}

GameFlowPrinter::~GameFlowPrinter()
{
	delete gameBoardConfig;
	delete gameBoard;
	delete villageBoards;
	delete currentPlayer;
}

bool GameFlowPrinter::initialize()
{
	if (GameController::current != nullptr && GameController::current->game_settings != nullptr)
	{
		*gameBoardConfig = GameController::current->game_settings->board->printIndexConfiguration();
		*gameBoard = GameController::current->game_settings->board->getBoardString();
		*currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayer()]->getID();

		villageBoards->reserve(GameController::current->game_settings->players->size());

		for (std::uint_fast8_t i{ 0 }; i < GameController::current->game_settings->players->size(); ++i)
		{
			villageBoards->push_back(GameController::current->game_settings->players->operator[](i)->getVillage().PrintGraph());
		}

		return true;
	}
	else
		throw UninitializedControllerException();

	return false;
}

void GameFlowPrinter::update()
{
	*gameBoard = GameController::current->game_settings->board->getBoardString();

	*currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayer()]->getID();

	for (std::uint_fast8_t i{ 0 }; i < villageBoards->size(); ++i)
		villageBoards->operator[](i) = GameController::current->game_settings->players->operator[](i)->getVillage().getBoardString();
}

void GameFlowPrinter::printGameBoardConfig()
{
	cout << "\n***GAME BOARD ID CONFIGURATION***\n" << *gameBoardConfig << '\n';
}

void GameFlowPrinter::printGameBoard() const
{
	cout << "\n***GAME BOARD CONTENT***\n" << *gameBoard << '\n';
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
