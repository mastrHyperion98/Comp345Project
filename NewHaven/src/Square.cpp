//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#include "Square.h"

using namespace std;

Square::Square(){
    position = nullptr;
    tile = nullptr;
    isVisited = new bool(false);
    isPlayed = new bool(false);
}

Square::Square(const Square &square) {
    position = new int(*square.position);
    if(square.tile != nullptr)
        tile = new HarvestTile(*square.tile);
    else
        tile = nullptr;
    isVisited = new bool(*square.isVisited);
    isPlayed = new bool(*square.isPlayed);
}

Square::~Square() = default;

void Square::setPosition(int* position){
    int *cpy = new int(*position);
    this->position = new int(*cpy);
    delete cpy;
    delete position;
}
int Square::getPosition() const{
    int *cpy = new int(*position);
    return *cpy;
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