#include "../src/Resources.h"
#include <iostream>

int main()
{
    HarvestTile tile;
    resourceTypes* content{ tile.getTileContent() };
    std::uint_least8_t* position{ tile.getPosition() };

    delete content;
    delete position;

    content = NULL;
    position = NULL;
    
    return 0;
}