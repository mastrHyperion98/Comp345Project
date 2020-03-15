#include <iostream>
#include "../src/GBMap.h"
#include "../src/Resources.h"
#include "../src/ResourceScore.h"
#include "../src/VGMap.h"
#include "../src/Resources.h"
#include "ResourceCalculator.h"

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

    HarvestTile ht{ new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT} };
   // ResourceTypes* rt{ new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD} };    //Full loop
    ResourceTypes* rt{ new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WHEAT} };    //Half loop
    ResourceTypes* resTop{ new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WOOD} };
    ResourceTypes* resBottom{ new ResourceTypes[4]{ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WHEAT, ResourceTypes::WHEAT} };
    ResourceTypes* resSide{ new ResourceTypes[4]{ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WHEAT} };

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

    ResourceTypes* t0{ (*map.board)[5].tile->getTileContent() },
            * t1{ (*map.board)[6].tile->getTileContent() },
            * t2{ (*map.board)[7].tile->getTileContent() },
            * t3{ (*map.board)[8].tile->getTileContent() },
            * t3_1{ (*map.board)[9].tile->getTileContent() },
            * t3_2{ (*map.board)[10].tile->getTileContent() },
            * t4{ (*map.board)[11].tile->getTileContent() },
            * t5{ (*map.board)[13].tile->getTileContent() },
            * t6{ (*map.board)[14].tile->getTileContent() },
            * t7{ (*map.board)[16].tile->getTileContent() },
            * t8{ (*map.board)[17].tile->getTileContent() },
            * t9{ (*map.board)[18].tile->getTileContent() },
            * t9_1{ (*map.board)[19].tile->getTileContent() };

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

    ResourceCalculator calculator;
    map.printIndexConfiguration();
    cout << "\n***The Asterisk denotes the position 13!***\n" << endl;
    int root;
    bool valid_root = false;
    for (int i = 0; i < 7; i++) {
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
            int* re = calculator.computeResources(
                    *map.getResourcedGraph(root)); //13 is the root tile, can be changed to any other valid tile.
            cout << '\n';
            cout << "WT: " << re[0] << "\t" << "SH: " << re[1]<< "\t" << "WD: " << re[2] << "\t" << "ST: " << re[3] << endl;
        }
    }
}