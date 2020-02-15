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
Square::~Square(){
    delete tile;
    delete position;
    delete isVisited;
}
void Square::setPosition(int position){
    this->position = &position;
}
int Square::getPosition(){
    return *position;
}
void Square::setTile(HarvestTile * tile){
    if(tile == 0)
        this->tile = tile;
    else{
        cerr << "ERROR: Tile " << *this->position << " already contains a tile!";
        throw 1;
    }
}
HarvestTile* Square::getTile(){
    return tile;
}