/*This file contains the functions and properties used by the New Haven Game Map.
 * The map is a connected graph implemented using the boost graph library.
 * Created by Steven on 2020-01-31.
 * Created for Concordia W 2020 Comp 345 New Haven Project
 */

// include boost adjacency_list
#include "boost/graph/adjacency_list.hpp"
// include the io stream library
#include <iostream>
// include the string library
#include <string>
// include GBMap header for functions calls etc.
#include "GBMap.h"
// we will be using the boost and std namespace
using namespace std;
using namespace boost;

// create a structure for the game map vertex data

 struct VertexData
{
    string *tile_type;
    int *id;
};


