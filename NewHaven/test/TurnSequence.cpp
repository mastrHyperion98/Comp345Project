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
        string resource_choice;
        cout << "Which resource type would you like?\n\tSheep\n\tStone\n\tWheat\n\tWood\nChoice:";
        cin >> resource_choice;

        if ((resource_choice != "SHEEP") || (resource_choice != "STONE") || (resource_choice != "WHEAT") || (resource_choice != "WOOD"))
            goto RESOURCE_CHOICE;

            // Todo: Implement a shipment tile using the resource chosen
            // Once the move is over, override the shipment tile with the actual drawn harvest tile
    }
}
