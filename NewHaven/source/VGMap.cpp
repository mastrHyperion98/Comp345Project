//
// Created by Nizz Wizz on 2020-02-05.
//

#include "VGMap.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/connected_components.hpp"
// include the io stream library
#include <iostream>
// include the string library
#include <string>

using namespace std;
using namespace boost;


VGMap::VGMap() {

}

// Define the deconstructor of the GameBoard Map
VGMap::~VGMap() = default;

// Function that goes and fetches the graph
Graph* VGMap::GetVillageBoard() {
    return VGMap::village_board;
}
// generate the graph
/*
The gameboard will be initiated in parts, based on the configuration of the board (aka # of players)
Each vertex (Square) will be labeled with a number. That number will be indentical to its index in the graph
and will start at 0 at the upper left most corner of the 2 player field. From there, the vertices will be created row by row.
It will be created in a similar way as a 2D Matrix.
*/
void VGMap::GenerateGraph() {
    CreateVillageField();

}
// create the center 5x5 field area
void VGMap::CreateVillageField() {

    for (int position = 0; position < 30; position++) {
        add_vertex(*village_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (position > 0 && position % 5 != 0)
            add_edge(position, position - 1, *village_board);
        (*village_board)[position].position = new int(position);

    }
    


    for (int position = 0; position < 25; position++) {
        add_edge(position, position + 5, *village_board);
    }


}


void VGMap::PrintGraph() {
    boost::print_graph(*village_board);
}

// Taken from the Boost Connected Graph Example
//https://www.boost.org/doc/libs/1_65_0/libs/graph/example/connected_components.cpp
// Prints the number of Connected Components and which vertex belongs to which component
// A component is a set of one or more nodes in which a path exists.
// In other words, if the graph is connected than there is only 1 component.
// If component 2 exists then there does not exists a path linking nodes from Component 1 and 2.
void VGMap::PrintConnectedGraph() {

    std::vector<int> component(num_vertices(*village_board));
    int num = connected_components(*village_board, &component[0]);

    std::vector<int>::size_type i;
    cout << "Total number of components: " << num << endl;
    for (i = 0; i != component.size(); ++i)
        cout << "Circle " << i <<" is in component " << component[i] << endl;
    cout << endl;
}
