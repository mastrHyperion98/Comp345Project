//
// Created by hyperion on 2020-02-20.
//

#include "InvalidConfigurationException.h"

const char* InvalidConfigurationException::what() const throw()
{
    return "ERROR: Invalid Board Configuration!";
}