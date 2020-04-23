//
// Created by hyperion on 2020-03-27.
//

#ifndef NEWHAVEN_GAMECONTROLLER_H
#define NEWHAVEN_GAMECONTROLLER_H
#include "Setting.h"
#include "GameObservers.h"
// create enum for the game state
enum States{NEW_TURN, SHARE_THE_WEALTH, END_TURN, PLAYED_HARVEST_TILE,
        PLAYING_HARVEST_TILE, BUILDING_VILLAGE, INITIAL, STANDBY, END_GAME};
typedef pair<Player*, int> entry;
typedef map<Player*, int> scores;
class GameController: public Observable {
public:
    GameController();
    GameController(const GameController & controller) = delete;
    GameController& operator=(const GameController& controller) = delete;
    ~GameController();
    bool initialize();
    void start();
    int getCurrentPlayerTurn(){return *current_turn_player;};
    int getCurrentSharePlayer(){return *current_share_player;};
    static GameController *current;
    Setting *game_settings;
    States getState();
private:
    ResourceTypes *original_shipment{nullptr};
    int *current_turn_player;
    States *game_state{new States(States::INITIAL)};
    int *current_share_player;
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
    void setState(States state);


    scores findWinner();
};


#endif //NEWHAVEN_GAMECONTROLLER_H
