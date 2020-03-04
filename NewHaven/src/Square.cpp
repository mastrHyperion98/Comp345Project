//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#include "Square.h"
#include <iostream>
using namespace std;

Square::Square() : visitedResource{ new bool[4]{ false, false, false, false } }, rootConnected{ new bool[4]{ false, false, false, false } }
{
    position = new int(-1);
    isVisited = new bool(false);
    isPlayed = new bool(false);
    tile = nullptr;
}

Square::Square(const Square& square) : visitedResource{ new bool[4] }, rootConnected{ new bool[4] }
{
    if(square.tile != nullptr) {
        tile = new HarvestTile();
        // use the operator overloader
        *tile = *square.tile;
    }
    else
        tile = nullptr;
    position = new int(*square.position);
    isVisited = new bool(*square.isVisited);
    isPlayed = new bool(*square.isPlayed);

    for (std::int_fast8_t i = 0; i < 4; i++)
    {
        visitedResource[i] = square.visitedResource[i];
        rootConnected[i] = square.rootConnected[i];
    }
}

Square & Square::operator=(const Square &square) {
    if(&square == this)
        return *this;
    else{
        delete position;
        delete isVisited;
        delete isPlayed;
        delete tile;
        delete[] visitedResource;
        delete[] rootConnected;
        position = new int(*square.position);
        isVisited = new bool(*square.isVisited);
        isPlayed = new bool(*square.isPlayed);
        tile = new HarvestTile(*square.tile);
        visitedResource = new bool[4];
        rootConnected = new bool[4];
        for(int i =0; i < 4; i++){
            visitedResource[i]=square.visitedResource[i];
            rootConnected[i]=square.rootConnected[i];
        }
    } return *this;
}

Square::~Square() {
    delete position;
    delete isVisited;
    delete isPlayed;
    delete[] visitedResource;
    delete[] rootConnected;
}
