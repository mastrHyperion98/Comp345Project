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
// I'm assuming it just wants to know the amount of resources available
void Player::resourceTracker() {
    resource_score->printScore();
}