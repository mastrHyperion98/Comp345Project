//
// Created by Steven Smith on 2020-02-20
// Exception created for Concordia W 2020 Comp 345 Assignment 1
//
// The exception is called when attempting to create a gameBoard without loading a configuration
//
#ifndef NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
#define NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
#include <exception>

class BoardConfigurationNotLoaded : public std::exception {
public:
    virtual const char* what() const throw();
};


#endif //NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
