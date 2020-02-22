#include "Calculations.h"
#include "../src/GBMap.h"
#include "../src/Resources.h"
#include <cstdlib>
#include <boost/graph/graph_utility.hpp>
#include <iostream>

// To check for adjacent tiles
bool ResourcesCollected::checkRight(int currentPosition){
    if (this->tiles.count(currentPosition+1) > 0)
        cout << "right side has tile\n";
    return true;
}
bool ResourcesCollected::checkLeft(int currentPosition){
    if (this->tiles.count(currentPosition-1) > 0)
        cout << "left side has tile\n";
    return true;
}
bool ResourcesCollected::checkBelow(int currentPosition){
    if (this->tiles.count(currentPosition+5) > 0)
        cout << "bottom side has tile\n";
    return true;
}
bool ResourcesCollected::checkAbove(int currentPosition){
    if (this->tiles.count(currentPosition-5) > 0)
        cout << "top side has tile\n";
    return true;
}

// To check for adjacent resources
int ResourcesCollected::checkRightAndBelow(ResourceTypes mainResource, ResourceTypes rightResource,
                                            ResourceTypes bottomResource){
    int total = 0;
    if (mainResource == rightResource) total += 1;
    if (mainResource == bottomResource) total += 1;
    cout << "main: " << mainResource << "\tright: " << rightResource << "\tbottom: " << bottomResource << "\ttotal: "
                                                                                                       << total <<"\n";
    return total;
}
int ResourcesCollected::checkLeftAndBelow(ResourceTypes mainResource, ResourceTypes leftResource,
                                           ResourceTypes bottomResource) {
    int total = 0;
    if (mainResource == leftResource) total += 1;
    if (mainResource == bottomResource) total += 1;
    cout << "main: " << mainResource << "\tleft: " << leftResource << "\tbottom: " << bottomResource << "\ttotal: "
                                                                                                     << total <<"\n";
    return total;
}
int ResourcesCollected::checkRightAndAbove(ResourceTypes mainResource, ResourceTypes rightResource,
                                            ResourceTypes aboveResource) {
    int total = 0;
    if (mainResource == rightResource) total += 1;
    if (mainResource == aboveResource) total += 1;
    cout << "main: " << mainResource << "\tright: " << rightResource << "\tabove: " << aboveResource << "\ttotal: "
                                                                                                     << total <<"\n";
    return total;
}

int ResourcesCollected::checkLeftAndAbove(ResourceTypes mainResource, ResourceTypes leftResource,
                                           ResourceTypes aboveResource) {
    int total = 0;
    if (mainResource == leftResource) total += 1;
    if (mainResource == aboveResource) total += 1;
    cout << "main: " << mainResource << "\tleft: " << leftResource << "\tabove: " << aboveResource << "\ttotal: "
                                                                                                   << total <<"\n";
    return total;
}

void ResourcesCollected::calculateResourcesCollected() {
    int topLeftResourcetotal = 1;
    int topRightResourceTotal = 1;
    int bottomRightResourceTotal = 1;
    int bottomLeftResourceTotal = 1;

    for (int i = 0; i < this->connectedNodes.size(); i++) {
        cout << "Tile - " << this->connectedNodes[i] << "\t\n";

        // Checks the resource orthogonally
        for (int j = 0; j < 4; j++) {
            cout << j << "-" << this->tiles[connectedNodes[i]][j] << " \t ";
            if (j == 0) {
                topLeftResourcetotal += checkRightAndBelow(this->tiles[connectedNodes[i]][0], this->tiles[connectedNodes[i]][1],
                                            this->tiles[connectedNodes[i]][3]);

            }else if (j == 1) {
                topRightResourceTotal += checkLeftAndBelow(this->tiles[connectedNodes[i]][1], this->tiles[connectedNodes[i]][0],
                                           this->tiles[connectedNodes[i]][2]);
            }else if (j == 2) {
                bottomRightResourceTotal += checkLeftAndAbove(this->tiles[connectedNodes[i]][2], this->tiles[connectedNodes[i]][3],
                                           this->tiles[connectedNodes[i]][1]);
            }else if (j == 3) {
                bottomLeftResourceTotal += checkRightAndAbove(this->tiles[connectedNodes[i]][3], this->tiles[connectedNodes[i]][2],
                                            this->tiles[connectedNodes[i]][0]);
            }
        }
        cout << "\n";
    }
    cout << "\n";

    // Checks adjacent tiles
    int currentPosition = this->connectedNodes.front();
    this->checkRight(currentPosition);
    this->checkLeft(currentPosition);
    this->checkBelow(currentPosition);
    this->checkAbove(currentPosition);
}


