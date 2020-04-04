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
    static GameController *current;
    Setting *game_settings;
private:
    ResourceTypes *original_shipment{nullptr};
    int *current_turn_player;
    void playTurn();
    int startingPlayer();
    bool hasGameEnded();
    void endGame();
    void restart();
    inline int selectTileOption();
    inline ResourceTypes selectResourceType();
    int playShipmentTile(ResourceTypes type, Player *player);
    inline void setOriginalShipmentTile(Player *player);
    void shareTheWealth();

};


#endif //NEWHAVEN_GAMECONTROLLER_H
