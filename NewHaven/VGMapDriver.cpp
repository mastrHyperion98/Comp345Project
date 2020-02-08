//
// Created by Nizz Wizz on 2020-02-05.
//

#include <iostream>
#include "source/VGMap.h"

using namespace std;
int main() {
    VGMap *vMap = new VGMap();
    cout << "\n***Generate Graph***\n" << endl;
    vMap->GenerateGraph();
    cout << "\n***PRINT GRAPH***\n" << endl;
    vMap->PrintGraph();
    cout << "\n***Print Connected Components***\n" << endl;
    vMap->PrintConnectedGraph();
    return 0;
}