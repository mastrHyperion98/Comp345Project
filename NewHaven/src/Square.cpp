//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#include "Square.h"

using namespace std;

Square::Square() : visitedResource{ new bool[4]{ false, false, false, false } }, rootConnected{ new bool[4]{ false, false, false, false } }
{
    position = nullptr;
    tile = nullptr;
    isVisited = new bool(false);
    isPlayed = new bool(false);
}

Square::Square(const Square& square) : visitedResource{ new bool[4] }, rootConnected{ new bool[4] }
{
    position = new int(*square.position);
    if(square.tile != nullptr)
        tile = new HarvestTile(*square.tile);
    else
        tile = nullptr;
    isVisited = new bool(*square.isVisited);
    isPlayed = new bool(*square.isPlayed);

    for (std::int_fast8_t i = 0; i < 4; i++)
    {
        visitedResource[i] = square.visitedResource[i];
        rootConnected[i] = square.rootConnected[i];
    }
}

Square::~Square() = default;

void Square::setPosition(int* position){
    int *cpy = new int(*position);
    this->position = new int(*cpy);
    delete cpy;
    delete position;
}
int Square::getPosition() const{
    return *position;
}
void Square::setTile(HarvestTile * tile){
    if(!*isPlayed && tile != nullptr) {
        this->tile = new HarvestTile(*tile);
        *isPlayed = true;
    }
    else {
        throw 1;
    }
}
HarvestTile* Square::getTile() const{
    HarvestTile* cpy =new HarvestTile(*tile);
    return cpy;
}
bool Square::getIsPlayed() {
        return *isPlayed;
}