//
// Created by hyperion on 2020-04-03.
// Student ID: 40057065
// Created for: Assingment 2 Concordia W2020 Comp 345 with Dr. Nora

/*
 * NewHavenMain is the driver for Assingment 2. In theory it is the driver for Part 2, but Part 2 encompasses the entire
 * assignment and as such we use it to show the entire test result for the entire Assignment. Part 1 does have a seperate driver.
 * However, it is also shown in this one.
 *
 * GameController is, as the name implies, the controller of the game. It guides the logic and unites all other components
 * together. As such it was designed to be used as a singleton. That is why we can use it as the driver for all the other parts
 *
 * To test part 4, without having to play the entire game, you can change the end_game condition in the GBMap.cpp (last function)
 */
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

