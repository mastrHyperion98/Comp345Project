#pragma once

#include <string>
#include <vector>
#include "GameObservers.h"

class GameFlowPrinter :public Observer
{
private:
	std::string* gameBoardConfig;
	std::string* gameBoard;
	std::vector<std::string>* villageBoards;
	std::string* currentPlayer;

public:
	GameFlowPrinter();
	GameFlowPrinter(const GameFlowPrinter&);
	GameFlowPrinter& operator=(const GameFlowPrinter&);
	~GameFlowPrinter();
	
	void update();
	void printGameBoardConfig();
	void printGameBoard() const;
	void printVillageBoard(const size_t&) const;
	void printCurrentPlayer() const;
};
