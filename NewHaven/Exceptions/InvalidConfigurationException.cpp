//
// Created by Steven Smith on 2020-02-20
// Exception created for Concordia W 2020 Comp 345 Assignment 1
//
// The exception is called when attempting to create a gameBoard with an invalid configuration
//

#include "InvalidConfigurationException.h"

const char* InvalidConfigurationException::what() const throw()
{
    return "ERROR: Invalid Board Configuration!";
}