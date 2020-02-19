//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#include "Square.h"

using namespace std;

Square::Square(){
    position = 0;
    tile = 0;
    isVisited = new bool(false);
    isPlayed = new bool(false);
}
Square::~Square() = default;

void Square::setPosition(int* position){
    this->position = position;
}
int Square::getPosition() const{
    return *position;
}
void Square::setTile(HarvestTile * tile){
    if(!*isPlayed) {
        this->tile = tile;
        *isPlayed = true;
    }
    else {
        throw 1;
    }
}
HarvestTile Square::getTile() const{
    return *tile;
}
bool Square::getIsPlayed() {
        return *isPlayed;
}