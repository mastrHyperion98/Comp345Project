#pragma once
#include <iostream>
#include "../src/GBMap.h"
#include "../src/Resources.h"
#include "../src/ResourceScore.h"
#include "../src/VGMap.h"
#include "../src/Resources.h"
#include "../src/ScoreCalculator.h"

using namespace std;
using namespace boost;
int main()
{
	GBMap map(0);

/*
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 */

	map.setTile(5, new HarvestTile);
	map.setTile(6, new HarvestTile);
	map.setTile(7, new HarvestTile);
	map.setTile(8, new HarvestTile);
	map.setTile(9, new HarvestTile);
	map.setTile(10, new HarvestTile);
	map.setTile(11, new HarvestTile);
	map.setTile(13, new HarvestTile);
	map.setTile(14, new HarvestTile);
	map.setTile(16, new HarvestTile);
	map.setTile(17, new HarvestTile);
	map.setTile(18, new HarvestTile);
	map.setTile(19, new HarvestTile);

	/*Creating a variable for every tile to store its content for the sole purpose of printing it to console.
	* They are all pointers because tileContent is an array.
	*/

	ResourceTypes* t0{ map.getSquare(5)->getTile()->getTileContent() },
	*t1{ map.getSquare(6)->getTile()->getTileContent() },
	*t2{ map.getSquare(7)->getTile()->getTileContent() },
	*t3{ map.getSquare(8)->getTile()->getTileContent() },
		*t3_1{ map.getSquare(9)->getTile()->getTileContent() },
		* t3_2{ map.getSquare(10)->getTile()->getTileContent() },
		*t4{ map.getSquare(11)->getTile()->getTileContent() },
		*t5{ map.getSquare(13)->getTile()->getTileContent() },
		*t6{ map.getSquare(14)->getTile()->getTileContent() },
		*t7{ map.getSquare(16)->getTile()->getTileContent() },
		*t8{ map.getSquare(17)->getTile()->getTileContent() },
		*t9{ map.getSquare(18)->getTile()->getTileContent() },
		* t9_1{ map.getSquare(19)->getTile()->getTileContent() };

	/*
	This printing part is where I printed the tiles for a visual support. We print line by line every row of the connected tiles seperating every string with a tab.
	When there is no tile, we create the blank space with 3 consecutive tabs.
	*/

	std::cout << '\n' << t0[0] << '\t' << t0[1] << '\t' << t1[0] << '\t' << t1[1] << '\t' << t2[0] << '\t' << t2[1] << '\t' << t3[0] << '\t' << t3[1] << '\t' << t3_1[0] << '\t' << t3_1[1] <<
		'\n' << t0[3] << '\t' << t0[2] << '\t' << t1[3] << '\t' << t1[2] << '\t' << t2[3] << '\t' << t2[2] << '\t' << t3[3] << '\t' << t3[2] << '\t' << t3_1[3] << '\t' << t3_1[2] <<
		"\n\n" << t3_2[0] << '\t' << t3_2[1] << '\t' << t4[0] << '\t' << t4[1] << '\t' << '\t' << "\t*" << t5[0] << "\t" << t5[1] << '\t' << t6[0] << '\t' << t6[1] <<
		'\n' << t3_2[3] << '\t' << t3_2[2] << '\t' << t4[3] << '\t' << t4[2] << '\t' << '\t' << '\t' << t5[3] << '\t' << t5[2] << '\t' << t6[3] << '\t' << t6[2] <<
		"\n\n" << '\t' << '\t' << t7[0] << '\t' << t7[1] << '\t' << t8[0] << '\t' << t8[1] << '\t' << t9[0] << '\t' << t9[1] << '\t' << t9_1[0] << '\t' << t9_1[1] <<
		'\n' << '\t' << '\t' << t7[3] << '\t' << t7[2] << '\t' << t8[3] << '\t' << t8[2] << '\t' << t9[3] << '\t' << t9[2] << '\t' << t9_1[3] << '\t' << t9_1[2] << "\n\n";

	/*
	Created a rootConnected attribute to the HarvestTile. I also created a visitedResource attribute. They're both an array of 4 elements like tileContent. In both cases, every element of the array represents a resource in the tileContent array.
	All resources of the starting tile are rooted. That means that we will only add to the score the resources equal and adjacent to them. Once an adjacent resource is added to the score, we make it visited as to not count it twice.
	When the resource adjacent to a root resource is counted, we also make it rooted so that resources equal and adjacent to it can also be counted. In this way all resource trails connected to the initial tile resources give each other the
	rooted property and the only resources that can be counted to the score are rooted ones.
	*/

	ResourceScore calculator;
    map.printIndexConfiguration();
	cout << "\n***The Asterisk denotes the position 13!***\n" << endl;
	int root;
    bool valid_root = false;
    for(int i = 0; i < 7; i++) {
        while (cout << " Please input a proper root from which to compute the resources gathered: " && !(cin >> root)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Invalid input; please re-enter.\n";
        }

        if (root >= 5 && root != 12 && root != 15 && root <= 19)
            valid_root = true;
        else {
            std::cout << "Invalid input; please re-enter.\n";
            valid_root = false;
            i--;
        }
        if(valid_root) {
            calculator.computeScore(
                    map.getConnectedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
            cout << '\n';
            calculator.printScore();
        }
    }


    cout << "\n******** VILLAGE GAME BOARD SCORE TEST ***************\n" << endl;
    ScoreCalculator s_calculator;
    // Create a deck of buildings
    BuildingDeck deck;
    // create a village map
    VGMap v_map;
    // now we need to populate the map board either manually or not
    cout << "POPULATING ROW 1: TOP ROW WITH 6 FACE-UP BUILDINGS";
    for(int i = 0; i < 5; i++){
        v_map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    v_map.flipMapBuilding(3);
    cout << "FLIPPING ONE BUILDING IN ROW 1 FACEDOWN THE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    for(int i = 5; i < 10; i++){
        v_map.setBuilding(i, deck.draw());
    }
    cout << "POPULATING ROW 2: TOP ROW WITH 6 FACE-UP BUILDINGS";
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    v_map.flipMapBuilding(3);
    cout << "FLIPPING THE BUILDING IN ROW 1 FACEUP THE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    cout << "POPULATING COLUMN 1: LEFT-MOST WITH 5 FACE-UP BUILDINGS";
    for(int i = 5; i < 26; i += 5){
        if(!v_map.getCircle(i).getIsPlayed())
            v_map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    v_map.flipMapBuilding(0);
    cout << "FLIPPING THE BUILDING IN ROW 1 AND COLUMN 1 FACEDOWN THE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    cout << "POPULATING COLUMN 5: RIGHT-MOST WITH 5 FACE-UP BUILDINGS";
    for(int i = 4; i < 30; i += 5){
        if(!v_map.getCircle(i).getIsPlayed())
            v_map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    cout << "POPULATING COLUMN 3: MIDDLE WITH 5 FACE-UP BUILDINGS";
    for(int i = 2; i < 28; i += 5){
        if(!v_map.getCircle(i).getIsPlayed())
            v_map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(v_map) << endl;
    v_map.flipMapBuilding(7);
    cout << "FLIPPING THE BUILDING IN ROW 2 AND COLUMN 3 FACEDOWN THE SCORE IS: " << s_calculator.getScore(v_map) << endl;

}
