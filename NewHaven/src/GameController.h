//
// Created by hyperion on 2020-03-27.
//

#ifndef NEWHAVEN_GAMECONTROLLER_H
#define NEWHAVEN_GAMECONTROLLER_H
#include "Setting.h"
#include "GameObservers.h"
#include <map>
class Setting;
typedef pair<Player*, int> entry;
typedef map<Player*, int> scores;
class GameController : public Observable
{
public:
    GameController();
    GameController(const GameController & controller) = delete;
    GameController& operator=(const GameController& controller) = delete;
    ~GameController();
    bool initialize();
    void start();
    int getCurrentPlayerTurn();
    static GameController *current;
    Setting *game_settings;
    bool *is_share_wealth{new bool{false}};
    int  *sw_player{new int{0}};
    map<string, bool> *controller_status{new map<string,bool>};
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

    scores findWinner();
};


#endif //NEWHAVEN_GAMECONTROLLER_H
