//
// Created by hyperion on 2020-02-27.
//

#ifndef NEWHAVEN_SCORECALCULATOR_H
#define NEWHAVEN_SCORECALCULATOR_H
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "../src/VGMap.h"
#include "../src/Resources.h"
#include <map>
#include <iostream>

using namespace std;
using namespace boost;

class ScoreCalculator {
public:
    ScoreCalculator();
    ScoreCalculator(const ScoreCalculator &cal);
    ScoreCalculator & operator = (ScoreCalculator & cal);
    ~ScoreCalculator();

    int getScore(VGMap village_map) const;
    const int *NUM_ROWS = new int(6);
    const int *NUM_COLS = new int(5);

private:
    map<int, int> *column_scores;
    map<int, int> *row_scores;
};


#endif //NEWHAVEN_SCORECALCULATOR_H
