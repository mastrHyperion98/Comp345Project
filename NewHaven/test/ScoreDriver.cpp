#include <iostream>
#include "../src/GBMap.h"
#include "../src/Resources.h"
#include "../src/VGMap.h"
#include "../src/Resources.h"
#include "ResourceTracker.h"

using namespace std;
using namespace boost;
int main() {
    GBMap map(0);
    /*
     * -  00 01 02 03 04 -
     * -  05 06 07 08 09 -
     * -  10 11 12 13 14 -
     * -  15 16 17 18 19 -
     * -  21 22 23 24 25 -
     */
    HarvestTile ht{new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT,
                                        ResourceTypes::WHEAT}};
    // ResourceTypes* rt{ new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD} };    //Full loop
    ResourceTypes *rt{new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WOOD,
                                           ResourceTypes::WHEAT}};    //Half loop
    ResourceTypes *resTop{
            new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WOOD}};
    ResourceTypes *resBottom{
            new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WHEAT, ResourceTypes::WHEAT}};
    ResourceTypes *resSide{
            new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WHEAT}};

    map.placeHarvestTile(5, *new HarvestTile(ht));
    map.placeHarvestTile(6, *new HarvestTile(resTop));
    map.placeHarvestTile(7, *new HarvestTile(resTop));
    map.placeHarvestTile(8, *new HarvestTile(resTop));
    map.placeHarvestTile(9, *new HarvestTile(ht));
    map.placeHarvestTile(10, *new HarvestTile(ht));
    map.placeHarvestTile(11, *new HarvestTile(resSide));
    map.placeHarvestTile(13, *new HarvestTile(rt));
    map.placeHarvestTile(14, *new HarvestTile(ht));
    map.placeHarvestTile(16, *new HarvestTile(resBottom));
    map.placeHarvestTile(17, *new HarvestTile(resBottom));
    map.placeHarvestTile(18, *new HarvestTile(resBottom));
    map.placeHarvestTile(19, *new HarvestTile(ht));

    /*Creating a variable for every tile to store its content for the sole purpose of printing it to console.
    * They are all pointers because tileContent is an array.
    */

    ResourceTypes *t0{(*map.board)[5].tile->getTileContent()},
            *t1{(*map.board)[6].tile->getTileContent()},
            *t2{(*map.board)[7].tile->getTileContent()},
            *t3{(*map.board)[8].tile->getTileContent()},
            *t3_1{(*map.board)[9].tile->getTileContent()},
            *t3_2{(*map.board)[10].tile->getTileContent()},
            *t4{(*map.board)[11].tile->getTileContent()},
            *t5{(*map.board)[13].tile->getTileContent()},
            *t6{(*map.board)[14].tile->getTileContent()},
            *t7{(*map.board)[16].tile->getTileContent()},
            *t8{(*map.board)[17].tile->getTileContent()},
            *t9{(*map.board)[18].tile->getTileContent()},
            *t9_1{(*map.board)[19].tile->getTileContent()};

    /*
    This printing part is where I printed the tiles for a visual support. We print line by line every row of the connected tiles seperating every string with a tab.
    When there is no tile, we create the blank space with 3 consecutive tabs.
    */

    std::cout << '\n' << t0[0] << '\t' << t0[1] << '\t' << t1[0] << '\t' << t1[1] << '\t' << t2[0] << '\t' << t2[1]
              << '\t' << t3[0] << '\t' << t3[1] << '\t' << t3_1[0] << '\t' << t3_1[1] <<
              '\n' << t0[3] << '\t' << t0[2] << '\t' << t1[3] << '\t' << t1[2] << '\t' << t2[3] << '\t' << t2[2] << '\t'
              << t3[3] << '\t' << t3[2] << '\t' << t3_1[3] << '\t' << t3_1[2] <<
              "\n\n" << t3_2[0] << '\t' << t3_2[1] << '\t' << t4[0] << '\t' << t4[1] << '\t' << '\t' << "\t*" << t5[0]
              << "\t" << t5[1] << '\t' << t6[0] << '\t' << t6[1] <<
              '\n' << t3_2[3] << '\t' << t3_2[2] << '\t' << t4[3] << '\t' << t4[2] << '\t' << '\t' << '\t' << t5[3]
              << '\t' << t5[2] << '\t' << t6[3] << '\t' << t6[2] <<
              "\n\n" << '\t' << '\t' << t7[0] << '\t' << t7[1] << '\t' << t8[0] << '\t' << t8[1] << '\t' << t9[0]
              << '\t' << t9[1] << '\t' << t9_1[0] << '\t' << t9_1[1] <<
              '\n' << '\t' << '\t' << t7[3] << '\t' << t7[2] << '\t' << t8[3] << '\t' << t8[2] << '\t' << t9[3] << '\t'
              << t9[2] << '\t' << t9_1[3] << '\t' << t9_1[2] << "\n\n";

    /*
    Created a rootConnected attribute to the HarvestTile. I also created a visitedResource attribute. They're both an array of 4 elements like tileContent. In both cases, every element of the array represents a resource in the tileContent array.
    All resources of the starting tile are rooted. That means that we will only add to the score the resources equal and adjacent to them. Once an adjacent resource is added to the score, we make it visited as to not count it twice.
    When the resource adjacent to a root resource is counted, we also make it rooted so that resources equal and adjacent to it can also be counted. In this way all resource trails connected to the initial tile resources give each other the
    rooted property and the only resources that can be counted to the score are rooted ones.
    */

    ResourceTracker calculator;
    map.printIndexConfiguration();
    cout << "\n***The Asterisk denotes the position 13!***\n" << endl;
    int root;
    bool valid_root = false;
    for (int i = 0; i <1; i++) {
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
        if (valid_root) {
            calculator.computeScore(
                    *map.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
            calculator.printScore();
        }
    }
/*
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 */     GBMap map3(0);
        GBMap map2(0);

        ResourceTypes *types1 = new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::SHEEP,
                                                     ResourceTypes::WOOD};
        ResourceTypes *types2 = new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::WOOD,
                                                     ResourceTypes::SHEEP};
        ResourceTypes *types3 = new ResourceTypes[4]{ResourceTypes::SHEEP, ResourceTypes::SHEEP, ResourceTypes::WOOD,
                                                     ResourceTypes::STONE};
        ResourceTypes *types4 = new ResourceTypes[4]{ResourceTypes::STONE, ResourceTypes::SHEEP, ResourceTypes::STONE,
                                                     ResourceTypes::WOOD};
        ResourceTypes *types5 = new ResourceTypes[4]{ResourceTypes::STONE, ResourceTypes::WOOD, ResourceTypes::SHEEP,
                                                     ResourceTypes::WOOD};
        ResourceTypes *types6 = new ResourceTypes[4]{ResourceTypes::STONE, ResourceTypes::WOOD, ResourceTypes::SHEEP,
                                                     ResourceTypes::WOOD};
        ResourceTypes *types7 = new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::SHEEP,
                                                     ResourceTypes::STONE};
        ResourceTypes *types8 = new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::SHEEP,
                                                     ResourceTypes::STONE};
        HarvestTile tile1{types1};
        HarvestTile tile2{types2};
        HarvestTile tile3{types3};
        HarvestTile tile4{types4};
        HarvestTile tile5{types5};
        HarvestTile tile6{types6};
        HarvestTile tile7{types7};
        HarvestTile tile8{types8};
        map3.placeHarvestTile(6, *(new HarvestTile(tile4)));
        map3.placeHarvestTile(7, *(new HarvestTile(tile3)));
        map3.placeHarvestTile(8, *(new HarvestTile(tile2)));
        map3.placeHarvestTile(11, *(new HarvestTile(tile5)));
        map3.placeHarvestTile(13, *(new HarvestTile(tile1)));
        map3.placeHarvestTile(16, *(new HarvestTile(tile6)));
        map3.placeHarvestTile(17, *(new HarvestTile(tile7)));
        map3.placeHarvestTile(18, *(new HarvestTile(tile8)));
        map2.placeHarvestTile(6, *(new HarvestTile(tile4)));
        map2.placeHarvestTile(7, *(new HarvestTile(tile3)));
        map2.placeHarvestTile(8, *(new HarvestTile(tile2)));
        map2.placeHarvestTile(11, *(new HarvestTile(tile5)));
        map2.placeHarvestTile(13, *(new HarvestTile(tile1)));

        std::cout << '\n'
                  << "ST\tSH\tSH\tSH\tSH\tSH" << '\n'
                  << "WD\tST\tST\tWD\tSH\tWD" << '\n'
                  << "ST\tWD\t \t \t*SH\tSH" << '\n'
                  << "WD\tSH\t \t \tWD\tSH" << '\n'
                  << "ST\tWD\tWD\tWD\tWD\tWD" << '\n'
                  << "WD\tSH\tST\tSH\tST\tSH" << '\n' << endl;
        /*
        Created a rootConnected attribute to the HarvestTile. I also created a visitedResource attribute. They're both an array of 4 elements like tileContent. In both cases, every element of the array represents a resource in the tileContent array.
        All resources of the starting tile are rooted. That means that we will only add to the score the resources equal and adjacent to them. Once an adjacent resource is added to the score, we make it visited as to not count it twice.
        When the resource adjacent to a root resource is counted, we also make it rooted so that resources equal and adjacent to it can also be counted. In this way all resource trails connected to the initial tile resources give each other the
        rooted property and the only resources that can be counted to the score are rooted ones.
        */

        map3.printIndexConfiguration();
        cout << "\n***MAP 1: The Asterisk denotes the position 13!***\n" << endl;
        valid_root = false;
        for (int i = 0; i < 3; i++) {
            while (cout << " Please input a proper root from which to compute the resources gathered: " &&
                   !(cin >> root)) {
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
            if (valid_root) {
                calculator.computeScore(
                        *map3.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
                calculator.printScore();
            }
        }

        map2.printIndexConfiguration();
        std::cout << '\n'
                  << "ST\tSH\tSH\tSH\tSH\tSH" << '\n'
                  << "WD\tST\tST\tWD\tSH\tWD" << '\n'
                  << "ST\tWD\t \t \t*SH\tSH" << '\n'
                  << "WD\tSH\t \t \tWD\tSH" << endl;
        cout << "\n***MAP 2: The Asterisk denotes the position 13!***\n" << endl;
        valid_root = false;
        for (int i = 0; i < 3; i++) {
            while (cout << " Please input a proper root from which to compute the resources gathered: " &&
                   !(cin >> root)) {
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
            if (valid_root) {
                calculator.computeScore(
                        *map2.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
                calculator.printScore();
            }
        }
    }
