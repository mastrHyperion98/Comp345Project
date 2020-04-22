
#ifndef NEWHAVEN_GAMESTATISTICOBSERVER_H
#define NEWHAVEN_GAMESTATISTICOBSERVER_H
#include "GameObservers.h"
#include <string>
class GameStatisticObserver: public Observer{
public:
    GameStatisticObserver();
    ~GameStatisticObserver();
    GameStatisticObserver(const GameStatisticObserver&);
    GameStatisticObserver& operator=(const GameStatisticObserver&);

    bool initialize();

    void update();
    void printGameBoard() const;
    void printVillageBoard(const std::string&) const;
    void printCurrentPlayer() const;
    void printPlayerBuildingCount(int& index) const;
    void printPlayerScore(int&) const;
private:
    std::string* gameBoard;
    std::string* currentPlayer;

    std::vector<std::string>* villageBoards;
    std::vector<int>* playerBuildingCount;
    std::vector<int>* playerScore;
};


#endif //NEWHAVEN_GAMESTATISTICOBSERVER_H
