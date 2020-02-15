//
// Created by hyperion on 2020-02-15.
//

#ifndef NEWHAVEN_SQUARE_H
#define NEWHAVEN_SQUARE_H
#include "Resources.h"
class Square
{
public:
    Square();
    ~Square();
    void setPosition(int position);
    int getPosition();
    void setTile(HarvestTile * tile);
    HarvestTile* getTile();
    bool *isVisited;
private:
    HarvestTile* tile;
    int *position;
};
#endif //NEWHAVEN_SQUARE_H
