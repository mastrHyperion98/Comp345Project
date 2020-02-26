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
#include <deque>
using namespace std;
using namespace boost;


VGMap::VGMap() {

}

// Define the deconstructor of the GameBoard Map
VGMap::~VGMap() = default;

// Function that goes and fetches the graph
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

    for (int vPosition = 0; vPosition < 30; vPosition++) {
        add_vertex(*village_board);
        // if it isnt the first element in a row then add the previous element as a neighbour to the undirected graph
        if (vPosition > 0 && vPosition % 5 != 0)
            add_edge(vPosition, vPosition - 1, *village_board);


        if (vPosition>=0 && vPosition<5) {
            (*village_board)[vPosition].vCost = new int(6);
            (*village_board)[vPosition].row = new int(0);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        if (vPosition>=5 && vPosition<10) {
            (*village_board)[vPosition].vCost = new int(5);
            (*village_board)[vPosition].row = new int(1);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        if (vPosition>=10 && vPosition<15) {
            (*village_board)[vPosition].vCost = new int(4);
            (*village_board)[vPosition].row = new int(2);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        if (vPosition>=15 && vPosition<20) {
            (*village_board)[vPosition].vCost = new int(3);
            (*village_board)[vPosition].row = new int(3);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }
        if (vPosition>=20 && vPosition<25) {
            (*village_board)[vPosition].vCost = new int(2);
            (*village_board)[vPosition].row = new int(4);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }

        if (vPosition>=25 && vPosition<30) {
            (*village_board)[vPosition].vCost = new int(1);
            (*village_board)[vPosition].row = new int(5);
            (*village_board)[vPosition].column = new int(vPosition % 5);
        }
       // (*village_board)[vPosition].none;
    }


    for (int vPosition = 0; vPosition < 25; vPosition++) {
        add_edge(vPosition, vPosition + 5, *village_board);
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

void VGMap::CalcScore(){
    for(int i = 0; i < 30; i++){
       vertex_v vertex = village_board->vertex_set()[i];
    }

}

ConnectedCircles VGMap::getConnectedColumn(int const column){
    ConnectedCircles graph;
    deque<vertex_v> root_queue;
    int origin_index = column % 5;
    auto vertex_set = village_board->vertex_set();
    vertex_v vertex = vertex_set[origin_index];
    vertex_v origin_v = add_vertex(graph);
    graph[origin_v] = (*village_board)[vertex];
    root_queue.push_back(vertex);

    while (!root_queue.empty()) {
        vertex = root_queue.front();
        *(*village_board)[vertex].isVisited = true;
        Graph::adjacency_iterator start, end;
        tie(start, end) = adjacent_vertices(vertex, *village_board);
        for (; start != end; ++start) {
            // create the next element
            vertex_v next_element = vertex_set[*start];
            if (*(*village_board)[next_element].column == column && !*(*village_board)[next_element].isVisited) {
                // if the next_element is in the same column then push to queue
                root_queue.push_back(next_element);
                // add a vertex to the connectedCircles graph
                vertex_v v = add_vertex(graph);
                // assign circle to the next element of the graph
                graph[v] = (*village_board)[next_element];
                // add an edge -- origin_v always in front
                add_edge(origin_v, v, graph);
                // before leaving set v as the new origin;
                origin_v = v;
                // break
                break;
            }
        }
        // remove the front of the queue when the for loop is over.
        root_queue.pop_front();
    }
    resetVisited();
// return the new graph
    return graph;

}

ConnectedCircles VGMap::getConnectedRow(int const row) {
    ConnectedCircles graph;
    // create a queue to keep track of the next element to traverse
    deque<vertex_v> root_queue;
    int origin_index = 5 * row;
    // define the vertexSet of Village Board
    auto vertex_set = village_board->vertex_set();
    // get vertex from village board
    vertex_v vertex = vertex_set[origin_index];
    // create new vertex in ConnectedGraph graph
    vertex_v origin_v = add_vertex(graph);
    // assign the circle from vertex to origin_v
    graph[origin_v] = (*village_board)[vertex];
    // push origin into queue
    root_queue.push_back(vertex);


    // while queue is not empty iterate
    while (!root_queue.empty()) {
        // get the head of the queue
        vertex = root_queue.front();
        *(*village_board)[vertex].isVisited = true;
        // define your adjacency iterator
        Graph::adjacency_iterator start, end;
        tie(start, end) = adjacent_vertices(vertex, *village_board);
        for (; start != end; ++start) {
            // create the next element
            vertex_v next_element = vertex_set[*start];
            if (*(*village_board)[next_element].row == row && !*(*village_board)[next_element].isVisited) {
                // if the next_element is in the same row then push to queue
                root_queue.push_back(next_element);
                // add a vertex to the connectedCircles graph
                vertex_v v = add_vertex(graph);
                // assign circle to the next element of the graph
                graph[v] = (*village_board)[next_element];
                // add an edge -- origin_v always in front
                add_edge(origin_v, v, graph);
                // before leaving set v as the new origin;
                origin_v = v;
                // break
                break;
            }
        }
        // remove the front of the queue when the for loop is over.
        root_queue.pop_front();
    }
    resetVisited();
// return the new graph
    return graph;
}

void VGMap::resetVisited() {
    for(int i; i < 30; i++){
         *(*village_board)[i].isVisited = false;
    }
}
