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

using namespace std;

//void loadBoard(string filepath);
void loadVBoard(string filepath);

int main(){
    // TODO  Add files for Village game board to be loaded
    string v_files[6] = {"../config/VGMapNum_0.config",
                       "../config/VGMapNum_1.config",
                       "../config/VGMapNum_2.config",
                       "../config/VGMapNum_3.config",
                       "../config/VGMapNum_4.config",
                       "../config/VGMapNum_5.config"
    };

// string files[8] = {"../config/GBMapConfig_0.config",
//                 "../config/GBMapConfig_1.config",
//                 "../config/GBMapConfig_2.config",
//                 "../config/GBMapConfig_3.config",
//                 "../config/GBMapConfig_4.config",
//                 "../config/GBMapConfig_5.config",
//                 "../config/GBMapConfig_6.config",
//                 "../config/GBMapConfig_7.config"
// };
//  loops through all the files for the gameboard and test all of them
// for(int i = 0; i < 8; i++){
//     cout << "Attempting to load game board configuration file: " << files[i] << endl;
//     loadBoard(files[i]);
//     cout << "\n";
// }

 for(int i = 0; i < 6; i++){
        cout << "Attempting to load game board configuration file: " << v_files[i] << endl;
        loadVBoard(v_files[i]);
        cout << "\n";
    }

    // TODO Add function and/or loop to test Village Game Boards.

}

void loadVBoard(string filepath){
    VGMapLoader v_loader;
    try {
        v_loader.loadVConfig(filepath);
        VGMap map = v_loader.generateVMap();
        map.PrintGraph();
    }catch(InvalidConfigurationException e){
        cerr << e.what() << endl;
    }
    catch (BoardConfigurationNotLoaded e){
        cerr << e.what() << endl;
    }
}

//void loadBoard(string filepath){
//    GBMapLoader loader;
//    try {
//        loader.loadConfig(filepath);
//        GBMap map = loader.generateMap();
//        map.printGraph();
//    }catch(InvalidConfigurationException e){
//        cerr << e.what() << endl;
//    }
//    catch (BoardConfigurationNotLoaded e){
//        cerr << e.what() << endl;
//    }
//}