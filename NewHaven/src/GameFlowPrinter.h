#pragma once

#include<string>

class GameFlowPrinter :public Observer
{
private:
	std::string* gameBoard;
	std::string* villageBoard;
	std::string* currentPlayer;
	std::string* latestPlayerAction;

public:
	GameFlowPrinter();
	GameFlowPrinter(const GameFlowPrinter&);
	GameFlowPrinter& operator=(const GameFlowPrinter&);
	~GameFlowPrinter();
	
	void update();
	void printGameBoard() const;
	void printVillageBoard() const;
	void printCurrentPlayer() const;
	void printPlayerAction() const;
};
