//
// Created by hyperion on 2020-02-15.
//

#include "Square.h"
#include <iostream>

using namespace std;

Square::Square(){
    position = 0;
    tile = 0;
    isVisited = new bool(false);
}
Square::~Square() = default;

void Square::setPosition(int* position){
    this->position = position;
}
int Square::getPosition() const{
    return *position;
}
void Square::setTile(HarvestTile * tile){
    if(this->tile == 0)
        this->tile = tile;
    else {
        throw 1;
    }
}
HarvestTile* Square::getTile() const{
    return tile;
}