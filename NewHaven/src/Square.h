//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#ifndef NEWHAVEN_SQUARE_H
#define NEWHAVEN_SQUARE_H

#include "Resources.h"

struct Square
{
public:
    bool *isVisited, *visitedResource, *rootConnected, *isPlayed;
    int *position;
    //HarvestTile* tile;
    Square();
    Square(const Square &square);
    Square &operator=(const Square &square);
    ~Square();
};
#endif //NEWHAVEN_SQUARE_H
