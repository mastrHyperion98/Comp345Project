//
// Created by Steven Smith on 2020-02-20.
// Created for: Concordia W 2020 Comp 345
// Implementation file for the GBMap Loader defines the signature for the methods that will be used to read a file
//
#include "GBMapLoader.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "../Exceptions/InvalidConfigurationException.h"

using namespace std;
// Reads filepath and returns true if the board was creation. It will either return false or an exception if it fails.
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
            throw InvalidConfigurationException();
        }
        if(line.length() > position+1) {
            string config = line.substr(position + 1);
            int board_config = -1;
            try {
                board_config = boost::lexical_cast<int>(config);
            } catch (std::exception e) {
                throw InvalidConfigurationException();
            }
            if (board_config >= 0 && board_config < 3) {
                this->game_board_configuration = board_config;
                return true;
            }
        }
            return false;
    }
    else {
        cerr << "ERROR: File either does not exist or cannot open file";
        // close the reader before returning
        reader.close();
        return false;
    }
}
// create a GBMap, set its configuration and generate the graph before returning it.
GBMap GBMapLoader::generateMap() {
    if(game_board_configuration != -1){
        GBMap *gb_map{new GBMap(game_board_configuration)};
        return gb_map;
    }
    else{
        throw BoardConfigurationNotLoaded();
    }
}