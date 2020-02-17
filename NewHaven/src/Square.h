//
// Created by hyperion on 2020-02-15.
// Concordia W 2020 Comp 345
//

#ifndef NEWHAVEN_SQUARE_H
#define NEWHAVEN_SQUARE_H

#include "Resources.h"

class Square
{
public:
    bool *isVisited;

    Square();
    ~Square();

    HarvestTile getTile() const;
    int getPosition() const;
    bool getIsPlayed();
    void setPosition(int* position);
    void setTile(HarvestTile * tile);

private:
    HarvestTile* tile;
    int *position;
    bool *isPlayed;
};
#endif //NEWHAVEN_SQUARE_H
