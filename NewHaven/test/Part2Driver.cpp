//
// Created by hyperion on 2020-04-03.
//
#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"

int main(){
    // create the game controller
    GameController controller;
    if(controller.initialize()){
        std::cout << "INITIALIZATION SUCCESSFUL!" << endl;
        try{
            controller.start();
        }catch(const UninitializedControllerException &e){
            std::cout << e.what()<< std::endl;
        }catch(const std::exception& e){
           std::cout << e.what() << std::endl;
        }
    }
    else{
        std::cerr << "FAILED TO INITIALIZE CONTROLLER! EXITING SETUP" << endl;
        return 1;
    }

    return 0;
}

