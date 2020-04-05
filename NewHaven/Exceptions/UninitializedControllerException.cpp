//
// Created by hyperion on 2020-03-27.
//

#include "UninitializedControllerException.h"
const char* UninitializedControllerException::what() const throw()
{
    return "Controller Not Initialized Exception";
}