//
// Created by hyperion on 2020-02-20.
//

#ifndef NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
#define NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
#include <exception>

class BoardConfigurationNotLoaded : public std::exception {
public:
    virtual const char* what() const throw();
};


#endif //NEWHAVEN_BOARDCONFIGURATIONNOTLOADED_H
