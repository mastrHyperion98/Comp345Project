//
// Created by hyperion on 2020-04-21.
//

#ifndef NEWHAVEN_TURNOBSERVER_H
#define NEWHAVEN_TURNOBSERVER_H

#include "GameObservers.h"
#include <string>
class TurnObserver: public Observer {
public:
    TurnObserver();
    ~TurnObserver();
    // update function override
    virtual void update();
private:
    void printTurnStart();
};


#endif //NEWHAVEN_TURNOBSERVER_H
