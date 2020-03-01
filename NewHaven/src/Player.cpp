#include "Player.h"
#include "Resources.h"
#include "VGMap.h"
#include "ResourceScore.h"

Player::Player(){
    this->hand = new Hand();
}

Player::~Player(){
    delete hand;
}

void Player::buildVillage() {
    // to be discussed
}

void Player::drawHarvestTile(HarvestDeck* harvestDeck) {
    this->hand->harvestTiles->push_back(harvestDeck->draw());
}

void Player::drawBuilding(BuildingDeck* buildingDeck) {
    this->hand->buildings->push_back(buildingDeck->draw());
}

void Player::placeHarvestTile() {
    // place tile on the main game board
}

void Player::calculateResources(ResourceScore* resourceScore) {
    score = resourceScore->score;
}

void Player::resourceTracker(ResourceScore* resourceScore) {
    resourceScore->printScore();
}
