#include <iostream>
#include <boost/graph/graph_utility.hpp>
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
    map->printGraph();
    cout << "\n***Print Connected Components***\n" << endl;
    map->printConnectedGraph();

    cout << "\n***RESOURCE TRAIL STARTING AT POS = 0***\n" << endl;
    ResourceTrails trail = map->getConnectedGraph(0);
    ResourceTrails::vertex_iterator vertexIt, vertexEnd;
    ResourceTrails::adjacency_iterator neighbourIt, neighbourEnd;
    tie(vertexIt, vertexEnd) = vertices(trail);
    for (; vertexIt != vertexEnd; ++vertexIt)
    {
        cout << *trail[*vertexIt].position << " is connected with ";
        tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, trail);
        for (; neighbourIt != neighbourEnd; ++neighbourIt)
            cout << *trail[*neighbourIt].position << " ";
        cout << "\n";
    }
    return 0;
}
