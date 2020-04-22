#pragma once
#include "VGMap.h"
#include "Resources.h"
#include "ScoreCalculator.h"
#include "ResourceTracker.h"
#include <string>
#include "GameObservers.h"


enum PStates{DRAWING_HARVEST, DRAWING_BUILDING, DRAWING_BPOOL, UNKNOWN};
class Player: public Observable
{
public:
    Player(string id);
    Player(const Player &player);
    ~Player();
    Player &operator = (const Player &player);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the game_board
    int placeHarvestTile();
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the building deck
    void drawBuilding(Building* building);
    // cannot implement yet. Requires the game_controller / main-loop / logic controller to be a singleton with references to the harvest tile
    void drawHarvestTile(HarvestTile* tile);
    void drawBuildingPool(Building*);
    // Returns the ResourceTracker object held by the player
    bool buildVillage();
    void calculateResources(ResourceTrails);
    void setVillage(VGMap);
    // Used to set the shipment tile in Player's hand
    void setShipmentTile(HarvestTile* shipmentTile);
    // Getter for shipment tile
    HarvestTile* getShipmentTile();
    void setShipmentPlayed();
    string getID();
    void printHarvestCards();
    void printBuildingCards();
    int calculateScore() const;
    VGMap getVillage() const;
    Hand getHand() const;
    PStates getState(){return  *state;};
    void attachObserverToVillage(Observer*);
private:
    VGMap *village;
    PStates *state{new PStates{UNKNOWN}};
    ScoreCalculator *vb_score;
    Hand *my_hand;
    string *id;
    void setState(PStates);
};
