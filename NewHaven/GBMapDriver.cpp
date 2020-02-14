#include <iostream>
#include "src/GBMap.h"

using namespace std;
int main() {
    GBMap *map = new GBMap();
    int configuration = 0;
    cout << "Enter the board configuration (0 = 2 players, 1 = 3 players, 2 = 4 players): ";
    cin >> configuration;
    map->setBoardConfig(configuration);
    cout << "\n***Generate Graph***\n" << endl;
    map->generateGraph();
    cout << "\n***PRINT GRAPH***\n" << endl;
   // map->printGraph();
    cout << "\n***Print Connected Components***\n" << endl;
   // map->printConnectedGraph();
   map->getConnectedGraph(0);
    return 0;
}
