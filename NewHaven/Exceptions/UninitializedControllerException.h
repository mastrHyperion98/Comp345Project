//
// Created by hyperion on 2020-03-27.
//

#ifndef NEWHAVEN_UNINITIALIZEDCONTROLLEREXCEPTION_H
#define NEWHAVEN_UNINITIALIZEDCONTROLLEREXCEPTION_H


class UninitializedControllerException: public std::exception {
public:
    virtual const char* what() const throw();
};



#endif //NEWHAVEN_UNINITIALIZEDCONTROLLEREXCEPTION_H
