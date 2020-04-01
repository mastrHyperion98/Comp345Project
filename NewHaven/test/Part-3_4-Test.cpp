//
// Created by Muher on 2020-03-25.
//
#include <iostream>
#include "Player.h"

void shareWealth() {
    auto *bDeck = new BuildingDeck();
    auto *hDeck = new HarvestDeck();

    // Initiating Player and their hand to replicate the game for just this part
    // In practice, this part comes to play later in a turn, not at the beginning.

    // Assume a 2-player game
    auto *player1 = new Player("Player1");
    auto *player2 = new Player("Player2");

    // Start of the game, each player should have 6 buildings and 2 Harvest Tiles
    for (int i = 0; i < 6; i ++){
        (*player1).drawBuilding(bDeck->draw());
        (*player2).drawBuilding(bDeck->draw());
    }
    for (int i = 0; i < 2; i++){
        (*player1).drawHarvestTile(hDeck->draw());
        (*player2).drawHarvestTile(hDeck->draw());
    }

    // Temporary trail to do this part, would use the actual trail in practice
    auto trail = new ResourceTrails;

    // Calculate Player1 's resource, this is the LEFTOVER resources other players can now use
    (*player1).calculateResources(*trail);
    std::map<ResourceTypes, std::uint_least16_t> leftover{*player1->resourceTracker()->score};

    // Now, we're in Player2's turn, as we move clockwise.
    *player2->resourceTracker()->score = leftover;

    cout << "Would you like to use the leftover resources to erect a building in your village?" << endl;

    MOVE_CHOICE:
    int move_choice;
    cout << "1\tErect a building.\n2\tPass\nChoice: ";
    cin >> move_choice;

    if(move_choice < 1 || move_choice > 2) {
        cout << "This is not a valid move. \t*Enter the number*\nSelect either:" << endl;
        goto MOVE_CHOICE;
    }

    if(move_choice == 1)
        (*player2).buildVillage();
    else if (move_choice == 2)
        //end turn;
        cout << "Moving on to the next player." << endl;
};