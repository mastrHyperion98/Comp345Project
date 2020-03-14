//
// Created by hyperion on 2020-03-11.
//

#include <iostream>
#include <ResourceCalculator.h>
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
    GBMap map2(0);
/*
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 */
    ResourceTypes *types1 = new ResourceTypes[4]{ResourceTypes::SHEEP,ResourceTypes::SHEEP,ResourceTypes::SHEEP,ResourceTypes::WOOD};
    ResourceTypes *types2 = new ResourceTypes[4]{ResourceTypes::SHEEP,ResourceTypes::SHEEP,ResourceTypes::WOOD,ResourceTypes::SHEEP};

    ResourceTypes *types3 = new ResourceTypes[4]{ResourceTypes::SHEEP,ResourceTypes::SHEEP,ResourceTypes::WOOD,ResourceTypes::STONE};
    ResourceTypes *types4 = new ResourceTypes[4]{ResourceTypes::STONE,ResourceTypes::SHEEP,ResourceTypes::STONE,ResourceTypes::WOOD};

    ResourceTypes *types5 = new ResourceTypes[4]{ResourceTypes::STONE,ResourceTypes::WOOD,ResourceTypes::SHEEP,ResourceTypes::WOOD};
    ResourceTypes *types6= new ResourceTypes[4]{ResourceTypes::STONE,ResourceTypes::WOOD,ResourceTypes::SHEEP,ResourceTypes::WOOD};
    ResourceTypes *types7 = new ResourceTypes[4]{ResourceTypes::WOOD,ResourceTypes::WOOD,ResourceTypes::SHEEP,ResourceTypes::STONE};
    ResourceTypes *types8 = new ResourceTypes[4]{ResourceTypes::WOOD,ResourceTypes::WOOD,ResourceTypes::SHEEP,ResourceTypes::STONE};



    HarvestTile tile1{types1};
    HarvestTile tile2{types2};
    HarvestTile tile3{types3};
    HarvestTile tile4{types4};
    HarvestTile tile5{types5};
    HarvestTile tile6{types6};
    HarvestTile tile7{types7};
    HarvestTile tile8{types8};

    map.placeHarvestTile(6, *(new HarvestTile(tile4)));
    map.placeHarvestTile(7, *(new HarvestTile(tile3)));
    map.placeHarvestTile(8, *(new HarvestTile(tile2)));
    map.placeHarvestTile(11, *(new HarvestTile(tile5)));
    map.placeHarvestTile(13, *(new HarvestTile(tile1)));
    map.placeHarvestTile(16, *(new HarvestTile(tile6)));
    map.placeHarvestTile(17, *(new HarvestTile(tile7)));
    map.placeHarvestTile(18, *(new HarvestTile(tile8)));
    map2.placeHarvestTile(6, *(new HarvestTile(tile4)));
    map2.placeHarvestTile(7, *(new HarvestTile(tile3)));
    map2.placeHarvestTile(8, *(new HarvestTile(tile2)));
    map2.placeHarvestTile(11, *(new HarvestTile(tile5)));
    map2.placeHarvestTile(13, *(new HarvestTile(tile1)));

    /*Creating a variable for every tile to store its content for the sole purpose of printing it to console.
    * They are all pointers because tileContent is an array.
    */
/*
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
*/
    /*
    This printing part is where I printed the tiles for a visual support. We print line by line every row of the connected tiles seperating every string with a tab.
    When there is no tile, we create the blank space with 3 consecutive tabs.
    */

    std::cout << '\n' << "ST\tSH\tSH\tSH\tSH\tSH" << '\n'
                      << "ST\tWD\tWD\tST\tWD\tSH" << '\n'
                      << "ST\tWD\t \t \t*SH\tSH" << '\n'
                      << "SH\tWD\t \t \tSH\tWD" << '\n'
                      << "ST\tWD\tWD\tWD\tWD\tWD" << '\n'
                      << "SH\tWD\tSH\tST\tSH\tST" << '\n' << endl;

    /*
    Created a rootConnected attribute to the HarvestTile. I also created a visitedResource attribute. They're both an array of 4 elements like tileContent. In both cases, every element of the array represents a resource in the tileContent array.
    All resources of the starting tile are rooted. That means that we will only add to the score the resources equal and adjacent to them. Once an adjacent resource is added to the score, we make it visited as to not count it twice.
    When the resource adjacent to a root resource is counted, we also make it rooted so that resources equal and adjacent to it can also be counted. In this way all resource trails connected to the initial tile resources give each other the
    rooted property and the only resources that can be counted to the score are rooted ones.
    */

    ResourceCalculator calculator;
    map.printIndexConfiguration();
    cout << "\n***MAP 1: The Asterisk denotes the position 13!***\n" << endl;
    int root;
    bool valid_root = false;
    for(int i = 0; i < 3; i++) {
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
           int* re = calculator.computeResources(
                    *map.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
            cout << '\n';
            cout << re[0] << "\t" << re[1]<< "\t" << re[2] << "\t" << re[3] << endl;
        }
    }


    std::cout << '\n' << "ST\tSH\tSH\tSH\tSH\tSH" << '\n'
              << "ST\tWD\tWD\tST\tWD\tSH" << '\n'
              << "ST\tWD\t \t \t*SH\tSH" << '\n'
              << "SH\tWD\t \t \tSH\tWD" << '\n' << endl;
    cout << "\n***MAP 2: The Asterisk denotes the position 13!***\n" << endl;
    valid_root = false;
    for(int i = 0; i < 3; i++) {
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
            int* re = calculator.computeResources(
                    *map.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
            cout << '\n';
            cout << re[0] << "\t" << re[1]<< "\t" << re[2] << "\t" << re[3] << endl;
        }
    }


}