#include "../src/Resources.h"
#include <iostream>

int main()
{/*
    HarvestDeck hDeck;
    HarvestTile* tile;
    ResourceTypes* tContent;
    std::uint_least8_t hDeckSize;
    std::uint_least8_t tPosition;

    for (std::uint_fast8_t i = 0; i < 60; i++)
    {
    tile = hDeck.draw();
    deckSize = hDeck.getDeckSize();
    tContent = tile->getTileContent();
    tPosition = tile->getPosition();

    std::cout << "We drew a card.\nDeck size: " << static_cast<int>(hDeckSize) << "\tPosition: "
        << static_cast<int>(tPosition) << '\n';

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
    /*
    for (std::uint_fast8_t i = 0; i < 144; i++)
    {
        bDeckSize = bDeck.getDeckSize();
        building = bDeck.draw();
        bType = building->getBuildingType();
        bNumber = building->getBuildingNumber();
        bPosition = building->getPosition();

        std::cout << "We drew a card.\nDeck size: " << static_cast<int>(bDeckSize) << "\tPosition: " << '\n' << "Building: " << static_cast<int>(bType)
            << "\tNumber: " << static_cast<int>(bNumber) << "\tPosition: " << static_cast<int>(bPosition) << "\n\n";
    }
    */
    return 0;
}