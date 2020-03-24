//
// Created by Steven Smith on 2020-02-20.
// Created for: Concordia W 2020 Comp 345
//
//  "You must deliver a file named MapLoaderDriver.cpp file that  contains  a  main
//  function  that  reads  various  files  and  successfully  creates  a  map  object
//  for valid map files, and rejects invalid map files of different kinds." - Assingment 1 Part 3
//
// Will test and try to load a bunch of files for Gameboard and Village Game Board
//
//#include "../src/GBMapLoader.h"
//#include "../src/GBMap.h"
#include "../src/VGMapLoader.h"
#include "../src/VGMap.h"
#include "../Exceptions/InvalidConfigurationException.h"
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "iostream"
#include "string"
#include "../src/GBMapLoader.h"

using namespace std;

void loadBoard(string filepath);
void loadVBoard(string filepath);

int main(){
    // TODO  Add files for Village game board to be loaded
    string v_files[4] = {"../config/VGMapNum_0.config",
                       "../config/VGMapNum_1.config",
                       "../config/VGMapNum_2.config",
                       "../config/VGMapNum_3.config"
    };
 for(int i = 0; i < 4; i++){
        cout << "Attempting to load village map configuration file: " << v_files[i] << endl;
        loadVBoard(v_files[i]);
        cout << "\n";
    }
}
void loadVBoard(string filepath){
    VGMapLoader v_loader;
    try {
        v_loader.loadVConfig(filepath);
        VGMap *map{v_loader.generateVMap()};
        cout << *map->name << endl;
        map->PrintGraph();
    }catch(InvalidConfigurationException e){
        cout << e.what() << endl;
    }
    catch (BoardConfigurationNotLoaded e){
        cout << e.what() << endl;
    }
}

