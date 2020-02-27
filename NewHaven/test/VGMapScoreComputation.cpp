//
// Created by steven smith on 2020-02-26.
// Creates randomly onto the VillageBoard and compute the score.
//
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "../src/VGMap.h"
#include "../src/Resources.h"
#include <map>
#include <iostream>

using namespace std;
using namespace boost;
int main(){
    // keep a map for the scores
    map<int, int> column_scores;
    map<int, int> row_scores;
    // populate the scores
    column_scores.insert(pair<int, int>(0, 5));
    column_scores.insert(pair<int, int>(1, 4));
    column_scores.insert(pair<int, int>(2, 3));
    column_scores.insert(pair<int, int>(3, 4));
    column_scores.insert(pair<int, int>(4, 5));
    row_scores.insert(pair<int, int>(0, 6));
    row_scores.insert(pair<int, int>(1, 5));
    row_scores.insert(pair<int, int>(2, 4));
    row_scores.insert(pair<int, int>(3, 3));
    row_scores.insert(pair<int, int>(4, 2));
    row_scores.insert(pair<int, int>(5, 1));
    // create ourselves a deck
    /*
     * The idea for the test is that we will create 6 buildings types (the same type) from # 1 to 6. To compute the score
     * we will place these 6 buildings. Since these are only "logic" tests and we do not yet a Controller to validate
     * user input or not and the boards are only containers. They will not validate to see if adjacent circles are of the
     * same type or not. I believe that is the job of the controller. The board does/should verify that the position exists
     * though and does prevent placing a building in a circle that already contains one.
     */

    BuildingDeck deck;
    // these are our 6 buildings. The building deck is not shuffled so they should in theory all be the same card.
    VGMap *map = new VGMap();
    Building  *buildings[6] = {deck.draw(), deck.draw(),deck.draw(), deck.draw(), deck.draw(), deck.draw()};

    // now the first test here will be a repeatable test. Namely, this implies the 1st row index 0 to 4

    for(int i = 0; i < 5; i++){
        Circle circle = map->getCircle(i);
        circle.setBuilding(buildings[i]);
        cout << "use a debug end point";
    }

    // now lets see what we will get as an output
    // fetch row 0

    int row = 0;
    ConnectedCircles graph = map->getConnectedRow(row);
    // now we traverse through the graph. However, these graphs have a peculiar property
    // namely they can be traversed as an array because of their structure.
    int score = 0;
    bool isIncomplete = false;
    bool isFlipped = false;
    int num_vertices = boost::num_vertices(graph);
    for(int i = 0; i < num_vertices; i++) {
        // now we traverse and compute points -- essentially we check if there is a circle without a building or
        // if there is a flipped down piece.
        Circle circle = graph[i];
        if (!circle.getIsPlayed())
          isIncomplete = true;
       else if(circle.getBuilding().isFlipped())
            isFlipped = true;
    }
   if(!isFlipped)
        score = 2 * row_scores[row];
    else if(!isIncomplete)
        score = row_scores[row];

    cout << score;

    return 1;
}