//
// Created by Steven Smith on 2020-02-20.
// Created for: Concordia W 2020 Comp 345
//

#include "GBMapLoader.h"
#include <iostream>
#include <fstream>

using namespace std;
bool GBMapLoader::loadConfig(std::string filepath) {

    // create reader stream
    fstream reader;
    // create file lines
    string line;
    // open our file
    reader.open(filepath, ios::in);
    // A valid valid contains only 1 line --> header: #config
    if (reader.good() && reader.is_open()) {
        int i = 0;
        reader >> line;
        reader.close();

        int position;
        position = line.find_first_of(':');

        string header = line.substr(0, position);
        if(header.compare("NEW_HAVEN_GAME_BOARD_LOADER_CONFIGURATION") != 0){
            cerr << "ERROR: This file is not a valid configuration";
            return false;
        }
        cout << header;
    }
    else {
        cerr << "ERROR: File either does not exist or cannot open file";
        // close the reader before returning
        reader.close();
        return false;
    }
}