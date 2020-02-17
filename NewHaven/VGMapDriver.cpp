//
// Created by Nizz Wizz on 2020-02-05.
//

#include <iostream>
#include "source/VGMap.h"

using namespace std;
int main() {
    int playerNum;
    cin >> playerNum;
    VGMap* vgMaps = NULL;
    vgMaps = new VGMap[playerNum];

    for(int i=0; i<=playerNum;++i){
        cout << "\n***Generate Graph***\n" << endl;
        vgMaps[i].GenerateGraph();
        cout << "\n***PRINT GRAPH***\n" << endl;
        vgMaps[i].PrintGraph();
        cout << "\n***Print Connected Components***\n" << endl;
        vgMaps[i].PrintConnectedGraph();

    }
    delete []vgMaps;
    return 0;
}