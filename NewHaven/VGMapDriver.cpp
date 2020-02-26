//
// Created by Nizz Wizz on 2020-02-05.
//

#include <iostream>
#include "source/VGMap.h"
#include "boost/graph/graph_utility.hpp"

using namespace std;
int main() {
    int playerNum;
    cin >> playerNum;
    VGMap* vgMaps = nullptr;
    vgMaps = new VGMap[playerNum];

    for(int i=0; i< playerNum;++i){
        cout << "\n***Generate Graph***\n" << endl;
        vgMaps[i].GenerateGraph();
        cout << "\n***PRINT GRAPH***\n" << endl;
        vgMaps[i].PrintGraph();
        cout << "\n***Print Connected Components***\n" << endl;
        vgMaps[i].PrintConnectedGraph();
        vgMaps[i].CalcScore();
    }
    cout << endl;
//    ConnectedCircles graph = vgMaps[0].getConnectedRow(3);
    ConnectedCircles graphC = vgMaps[0].getConnectedColumn(4);
    boost::print_graph(graphC);

    delete[] vgMaps;
    return 0;
}