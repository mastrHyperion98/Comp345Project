//
// Created by hyperion on 2020-02-27.
//

#include "ScoreCalculator.h"

ScoreCalculator::ScoreCalculator(){
    column_scores = new map<int,int>;
    row_scores = new map<int,int>;
    column_scores->insert(pair<int, int>(0, 5));
    column_scores->insert(pair<int, int>(1, 4));
    column_scores->insert(pair<int, int>(2, 3));
    column_scores->insert(pair<int, int>(3, 4));
    column_scores->insert(pair<int, int>(4, 5));
    row_scores->insert(pair<int, int>(0, 6));
    row_scores->insert(pair<int, int>(1, 5));
    row_scores->insert(pair<int, int>(2, 4));
    row_scores->insert(pair<int, int>(3, 3));
    row_scores->insert(pair<int, int>(4, 2));
    row_scores->insert(pair<int, int>(5, 1));
}

ScoreCalculator::~ScoreCalculator() {
    delete column_scores;
    delete row_scores;
    delete NUM_ROWS;
    delete NUM_COLS;
}

ScoreCalculator::ScoreCalculator(const ScoreCalculator &cal){
    column_scores = new map<int,int>(*cal.column_scores);
    row_scores = new map<int,int>(*cal.row_scores);
}
ScoreCalculator & ScoreCalculator::operator = (ScoreCalculator & cal){
    *column_scores = *cal.column_scores;
    *row_scores =*cal.row_scores;

    return *this;
}


int ScoreCalculator::getScore( VGMap village_map) const{
int score = 0;

for(int i = 0; i < *NUM_ROWS; i++){
    ConnectedCircles graph = village_map.getConnectedRow(i);
    int num_vertices = boost::num_vertices(graph);
    bool isFlippedDown = false;
    bool isComplete = true;

    for(int j = 0; j < num_vertices; j++){
        if(!*graph[j].isPlayed) {
            isComplete = false;
            break;
        }
        else if(!graph[j].building->isFlipped())
            isFlippedDown = true;
    }

    if(!isFlippedDown && isComplete)
        score = score + (2 * (*row_scores)[i]);
    else if(isFlippedDown && isComplete)
        score = score + (*row_scores)[i];
}

// repeat above for columns

    for(int i = 0; i < *NUM_COLS; i++){
        ConnectedCircles graph = village_map.getConnectedColumn(i);
        int num_vertices = boost::num_vertices(graph);
        bool isFlippedDown = false;
        bool isComplete = true;

        for(int j = 0; j < num_vertices; j++){
            if(!*graph[j].isPlayed) {
                isComplete = false;
                break;
            }
            else if(!graph[j].building->isFlipped())
                isFlippedDown = true;
        }

        if(!isFlippedDown && isComplete)
            score = score + (2 * (*column_scores)[i]);
        else if(isFlippedDown && isComplete)
            score = score + (*column_scores)[i];
    }
return score;
}