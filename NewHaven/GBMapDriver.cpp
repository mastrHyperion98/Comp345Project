#include <iostream>
#include "source/GBMap.h"

using namespace std;
int main() {
    GBMap *map = new GBMap();
    int configuration = 0;
    cout << "Enter the board configuration (0 = 2 players, 1 = 3 players, 2 = 4 players): ";
    cin >> configuration;
    map->SetBoardConfig(configuration);
    cout << "\n***Generate Graph***\n" << endl;
    map->GenerateGraph();
    cout << "\n***PRINT GRAPH***\n" << endl;
    map->PrintGraph();
    cout << "\n***Print Connected Components***\n" << endl;
    map->PrintConnectedGraph();
    return 0;
}
