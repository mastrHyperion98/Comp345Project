#include "Player.h"

Player::Player(){
    village = new VGMap();
    resource_score = new ResourceScore();
    vb_score = new ScoreCalculator();
    my_hand = new Hand();
}

Player::Player(const Player &player) {
    village = new VGMap(*player.village);
    resource_score = new ResourceScore(*player.resource_score);
    vb_score = new ScoreCalculator(*player.vb_score);
    my_hand = new Hand(*player.my_hand);
}

Player::~Player(){
    delete village;
    delete resource_score;
    delete vb_score;
    delete my_hand;
}

Player& Player::operator=(const Player &player) {
    // nullptr and self assignment guard
    if(&player == this || &player == nullptr)
        return *this;
    else{
        // use assignment operator overload
        *village = *player.village;
        *resource_score = *player.resource_score;
        *vb_score = *player.vb_score;
        *my_hand = *player.my_hand;
    }
    return *this;
}
// I'm assuming it just wants to know the amount of resources available?
void Player::resourceTracker() {
    resource_score->printScore();
}

void Player::calculateResources(ResourceTrails trail) {
    resource_score->computeScore(trail);
}

bool Player::buildVillage(Building & building, int position){
    std::uint_least16_t cost = 0;
    if(building.isFlipped())
        cost = building.getBuildingNumber();
    else
        cost = village->getCircle(position).getVCost();

    ResourceTypes type=building.getBuildingType();
    if(resource_score->hasResources(type, cost)) {
        village->setBuilding(position, &building);
        resource_score->consumeResources(type, cost);
        return true;
    }
    return false;
}

bool Player::placeHarvestTile(HarvestTile& tile, int position) {

}

void Player::drawBuilding() {

}

void Player::drawHarvestTile() {
    
}

