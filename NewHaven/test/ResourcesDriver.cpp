#include "../src/Resources.h"
#include <iostream>

int main()
{
    HarvestDeck hDeck;
    HarvestTile* tile;
    ResourceTypes* tContent;
    std::uint_least8_t hDeckSize;
    std::uint_least8_t tPosition;
/*
    for (std::uint_fast8_t i = 0; i < 60; i++)
    {
    tile = hDeck.draw();
    hDeckSize = hDeck.getDeckSize();
    tContent = tile->getTileContent();

    std::cout << "We drew a card.\nDeck size: " << static_cast<int>(hDeckSize) << '\n';

    std::cout << tContent[0] << '\t' << tContent[1] << '\n' << tContent[3] << '\t' << tContent[2] << "\n\n";
    
    tile->rotateTileClockwise();
    delete tContent;
    tContent = tile->getTileContent();

    std::cout << tContent[0] << '\t' << tContent[1] << '\n' << tContent[3] << '\t' << tContent[2] << "\n\n";

    tile->rotateTileCounterClockwise();
    delete tContent;
    tContent = tile->getTileContent();

    std::cout << tContent[0] << '\t' << tContent[1] << '\n' << tContent[3] << '\t' << tContent[2] << "\n\n";
    
    delete tContent;
    }*/
    
    BuildingDeck bDeck;
    std::uint_least8_t bDeckSize;
    Building* building;
    ResourceTypes bType;
    std::uint_least8_t bNumber;
    std::uint_least8_t bPosition;
    bool side;
    
    for (std::uint_fast8_t i = 0; i < 144; i++)
    {
        building = bDeck.draw();
        bDeckSize = bDeck.getDeckSize();
        bType = building->getBuildingType();
        bNumber = building->getBuildingNumber();
        side = building->isFlipped();

        std::cout << "We drew a card.\nDeck size: " << static_cast<int>(bDeckSize) << "\nBuilding: " << bType
            << "\tNumber: " << static_cast<int>(bNumber)
            << "\tFace up: " << (side ? "true" : "false") << "\nWe flipped it.\nFace up: "
            << (building->flipCard() ? "true" : "false") << "\n\n";
    }
    
    return 0;
}