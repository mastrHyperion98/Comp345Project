//
// Created by Steven Smith on 2020-02-20.
// Created for: Concordia W 2020 Comp 345
//
#include "../src/GBMapLoader.h"
#include "../src/GBMap.h"
#include "../Exceptions/InvalidConfigurationException.h"
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "iostream"
#include "string"

using namespace std;

void loadBoard(string filepath);

int main(){
 string files[8] = {"../config/GBMapConfig_0.config",
                 "../config/GBMapConfig_1.config",
                 "../config/GBMapConfig_2.config",
                 "../config/GBMapConfig_3.config",
                 "../config/GBMapConfig_4.config",
                 "../config/GBMapConfig_5.config",
                 "../config/GBMapConfig_6.config",
                 "../config/GBMapConfig_7.config"
 };

 for(int i = 0; i < 8; i++){
     cout << "Attempting to load game board configuration file: " << files[i] << endl;
     loadBoard(files[i]);
     cout << "\n";
 }
}
void loadBoard(string filepath){
    GBMapLoader loader;
    try {
        loader.loadConfig(filepath);
        GBMap map = loader.generateMap();
        map.printGraph();
    }catch(InvalidConfigurationException e){
        cerr << e.what() << endl;
    }
    catch (BoardConfigurationNotLoaded e){
        cerr << e.what() << endl;
    }
}