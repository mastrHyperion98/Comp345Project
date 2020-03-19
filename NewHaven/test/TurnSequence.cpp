//
// Created by Muher on 2020-03-11.
//

#include <iostream>
#include "Player.h"
#include "Resources.h"

using namespace std;

int main(){
    // *** This is the sequence of the currently active player ***

    // Initiate decks
    auto *bDeck = new BuildingDeck();
    auto *hDeck = new HarvestDeck();

    auto *player = new Player(); // Initiate player

    // Start of the game, each player should have 6 buildings and 2 Harvest Tiles
    for (int i = 0; i < 5; i ++)
        (*player).drawBuilding(*bDeck->draw()); // Player draws a building from the deck
    for (int i = 0; i < 2; i++)
        (*player).drawHarvestTile(*hDeck->draw()); //Player draws a harvest tile from the deck

    // This tile is kept FACE DOWN until played.
    HarvestTile *shipmentTilePtr;
    HarvestTile shipmentTile = *hDeck->draw();

    shipmentTilePtr = &shipmentTile;

    // Testing output of shipment tile
    for (std::uint_fast8_t i = 0; i < 4; i++)
    {
         cout << (*shipmentTilePtr).getTileContent()[i] << "\t";
    }
    cout << endl;

    // 1. Player chooses to play either a harvest or shipment tile
    cout << "Your turn! What would you like to do? Enter the number for the move you'd like to make." << endl;

    MOVE_CHOICE:
    int move_choice;
    cout << "1\tPlay a Harvest tile from your possession\n2\tPlay with your Shipment tile.\nChoice: ";
    cin >> move_choice;

    if(move_choice < 1 || move_choice > 2) {
        cout << "This is not a valid move. Select either:" << endl;
        goto MOVE_CHOICE;
    }

    if(move_choice == 1)
        (*player).placeHarvestTile();
    else if (move_choice == 2){
        RESOURCE_CHOICE:
        int resource_choice;
        cout << "Which resource type would you like?\n\t1 - Sheep\n\t2 - Stone\n\t3 - Wood\n\t4 - Wheat\nChoice: ";
        cin >> resource_choice;

        // Make sure player chooses between the 4 options provided
        if (resource_choice < 1  || resource_choice > 4)
            goto RESOURCE_CHOICE;

        ResourceTypes* shipmentResource = new ResourceTypes[4];
        ResourceTypes choice;

        // Depending on player choice, we assign the ResourceTypes choice
        if (resource_choice == 1)
            choice = ResourceTypes::SHEEP;
        else if (resource_choice == 2)
            choice = ResourceTypes::STONE;
        else if (resource_choice == 3)
            choice = ResourceTypes::WOOD;
        else if (resource_choice == 4)
            choice = ResourceTypes::WHEAT;

        // Based on the selection, we then assign the 4 values in the array with the same resource
        for (std::uint_fast8_t i = 0; i < 4; i++)
        {
            shipmentResource[i] = choice;
        }

        // This is the temporary shipment tile we use for that round.
        HarvestTile* tempShipmentTile = new HarvestTile(shipmentResource);

        // Player draws this content, we have shipmentTile;
        (*player).drawHarvestTile(*shipmentTilePtr);

        // Point the shipment tile to the temporary resource tile player chose
        shipmentTilePtr = tempShipmentTile;

        // Places the shipment tile at the appropriate position.
        (*player).placeShipmentTile();

        // *IMPORTANT* Requires the map driver for the resource trail
        //(*player).resourceTracker = (*player).calculateResources();

        // *IMPORTANT*, this part needs to be done at the start of the round
        // the NEXT time the player plays. This way we can count the resources for
        // the intiial round, then convert it to normal for the start of the next round.
        // I'll leave this here for this driver for now.
        // Point the shipment tile back to the original tile
        *shipmentTilePtr = shipmentTile;
    }
}
