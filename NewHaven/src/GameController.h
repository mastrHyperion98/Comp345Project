//
// Created by hyperion on 2020-03-27.
//

#ifndef NEWHAVEN_GAMECONTROLLER_H
#define NEWHAVEN_GAMECONTROLLER_H
#include "Setting.h"

class GameController {
public:
    GameController();
    GameController(const GameController & controller);
    GameController& operator=(const GameController& controller);
    ~GameController();
    bool initialize();
    void start();

private:
    Setting *game_settings;
    int *current_turn_player;
    void playTurn();
    int startingPlayer();
    bool hasGameEnded();
    void endGame();
    void restart();
    inline int selectTileOption();
};


#endif //NEWHAVEN_GAMECONTROLLER_H
