//
// Created by hyperion on 2020-02-20.
//

#ifndef NEWHAVEN_INVALIDCONFIGURATIONEXCEPTION_H
#define NEWHAVEN_INVALIDCONFIGURATIONEXCEPTION_H
#include <exception>

class InvalidConfigurationException: public std::exception
{
public:
    virtual const char* what() const throw();
};


#endif //NEWHAVEN_INVALIDCONFIGURATIONEXCEPTION_H
