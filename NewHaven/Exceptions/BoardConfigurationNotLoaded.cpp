//
// Created by Steven Smith on 2020-02-20
// Exception created for Concordia W 2020 Comp 345 Assignment 1
//
// The exception is called when attempting to create a gameBoard without loading a configuration
//

#include "BoardConfigurationNotLoaded.h"
const char* BoardConfigurationNotLoaded::what() const throw()
{
    return "Board Configuration has not been loaded!";
}