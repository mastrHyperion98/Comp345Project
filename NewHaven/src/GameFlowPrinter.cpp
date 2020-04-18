#include "GameFlowPrinter.h"
#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

GameFlowPrinter::GameFlowPrinter()
{
	if (GameController::current->game_settings == nullptr)
		throw UninitializedControllerException();
	else
	{
		gameBoardConfig = new std::string(GameController::current->game_settings->board->printIndexConfiguration());
		gameBoard = new string(GameController::current->game_settings->board->getBoardString());
		villageBoards = new std::vector<std::string>(GameController::current->game_settings->players->size());
		currentPlayer = new std::string((*GameController::current->game_settings->players)[GameController::current->getCurrentPlayer()]->getID());

		for (std::uint_fast8_t i{ 0 }; i < GameController::current->game_settings->players->size(); ++i)
		{
			villageBoards->operator[](i) = GameController::current->game_settings->players->operator[](i)->getVillage().PrintGraph();
		}
	}
}

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
	delete gameBoard;
	delete villageBoards;
	delete currentPlayer;
}

void GameFlowPrinter::update()
{
	if (*gameBoard != GameController::current->game_settings->board->getBoardString())
		*gameBoard = GameController::current->game_settings->board->getBoardString();

	if (*currentPlayer != (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayer()]->getID())
		*currentPlayer = (*GameController::current->game_settings->players)[GameController::current->getCurrentPlayer()]->getID();

	for (std::uint_fast8_t i{ 0 }; i < villageBoards->size(); ++i)
	{
		VGMap village{ GameController::current->game_settings->players->operator[](i)->getVillage() };

		if (village.getBoardString() != villageBoards->operator[](i))
		{
			villageBoards->operator[](i) = village.getBoardString();
			break;
		}
	}
}

void GameFlowPrinter::printGameBoardConfig()
{
	cout << "\n* **GAME BOARD ID CONFIGURATION***\n" << gameBoardConfig << '\n';
}

void GameFlowPrinter::printGameBoard() const
{
	cout << "\n***GAME BOARD CONTENT***\n" << gameBoard << '\n';
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
	cout << "CURRENT PLAYER: " << currentPlayer << '\n';
}
