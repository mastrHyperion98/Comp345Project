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
#include "../src/ScoreCalculator.h"

using namespace std;
using namespace boost;
int main(){
    // create ScoreCalculator object
    ScoreCalculator s_calculator;
    // Create a deck of buildings
    BuildingDeck deck;
    // create a village map
    VGMap map;
    // now we need to populate the map board either manually or not
    cout << "POPULATING ROW 1: TOP ROW WITH 6 FACE-UP BUILDINGS";
    for(int i = 0; i < 5; i++){
        map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(map) << endl;
    map.getCircle(3).getBuilding().flipCard();
    cout << "FLIPPING ONE BUILDING IN ROW 1 FACEDOWN THE SCORE IS: " << s_calculator.getScore(map) << endl;
    for(int i = 5; i < 10; i++){
        map.setBuilding(i, deck.draw());
    }
    cout << "POPULATING ROW 2: TOP ROW WITH 6 FACE-UP BUILDINGS";
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(map) << endl;
    map.getCircle(3).getBuilding().flipCard();
    cout << "FLIPPING THE BUILDING IN ROW 1 FACEUP THE SCORE IS: " << s_calculator.getScore(map) << endl;
    cout << "POPULATING COLUMN 1: LEFT-MOST WITH 5 FACE-UP BUILDINGS";
    for(int i = 5; i < 26; i += 5){
        if(!map.getCircle(i).getIsPlayed())
            map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(map) << endl;
    map.getCircle(0).getBuilding().flipCard();
    cout << "FLIPPING THE BUILDING IN ROW 1 AND COLUMN 1 FACEDOWN THE SCORE IS: " << s_calculator.getScore(map) << endl;
    cout << "POPULATING COLUMN 5: RIGHT-MOST WITH 5 FACE-UP BUILDINGS";
    for(int i = 4; i < 30; i += 5){
        if(!map.getCircle(i).getIsPlayed())
            map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(map) << endl;
    cout << "POPULATING COLUMN 3: MIDDLE WITH 5 FACE-UP BUILDINGS";
    for(int i = 2; i < 28; i += 5){
        if(!map.getCircle(i).getIsPlayed())
            map.setBuilding(i, deck.draw());
    }
    cout << "\tTHE SCORE IS: " << s_calculator.getScore(map) << endl;
    map.getCircle(7).getBuilding().flipCard();
    cout << "FLIPPING THE BUILDING IN ROW 2 AND COLUMN 3 FACEDOWN THE SCORE IS: " << s_calculator.getScore(map) << endl;


    return 1;
}