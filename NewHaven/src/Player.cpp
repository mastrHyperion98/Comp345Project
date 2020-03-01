#include "Player.h"
#include "Resources.h"
#include "VGMap.h"
#include "ResourceScore.h"

Player::Player(){default;}

Player::~Player(){}

void Player::buildVillage() {}(){
// to be discussed
}

void Player::drawHarvestTile() {
    Player->hand->harvestTiles = HarvestDeck->darw();
}

void Player::drawBuilding() {
    Player->hand->buildings = BuildingDeck->draw();
}

void Player::placeHarvestTile() {
    // place tile on the main game board
}

void Player::calculateResources() {
    score = ResourceScore->score;
}

void Player::resourceTracker() {
    ResourceScore->printScore();
}
