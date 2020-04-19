#pragma once

#include <string>
#include <vector>
#include "GameObservers.h"

class GameFlowPrinter :public Observer
{
private:
	std::string* gameBoardConfig;
	std::string* gameBoard;
	std::string* currentPlayer;

	std::vector<std::string>* villageBoards;
	std::vector<int>* playerBuildingCount;
	std::vector<int>* playerScore;

public:
	GameFlowPrinter();
	GameFlowPrinter(const GameFlowPrinter&);
	GameFlowPrinter& operator=(const GameFlowPrinter&);
	~GameFlowPrinter();

	bool initialize();
	
	void update();
	void printGameBoardConfig();
	void printGameBoard() const;
	void printVillageBoard(const std::string&) const;
	void printCurrentPlayer() const;
	void printPlayerBuildingCount(int& index) const;
	void printPlayerScore(int&) const;
	void printNewTurn() const;
};
