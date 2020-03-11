//
// Created by Nizz Wizz on 2020-02-27.
//

#include "VGMapLoader.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include "../Exceptions/BoardConfigurationNotLoaded.h"
#include "../Exceptions/InvalidConfigurationException.h"

using namespace std;
// Reads filepath and returns true if the board was creation. It will either return false or an exception if it fails.
bool VGMapLoader::loadVConfig(std::string filepath) {

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
        if(header.compare("NEW_HAVEN_VILLAGE_BOARD_LOADER_NUM") != 0){
            throw InvalidConfigurationException();
        }
        if(line.length() > position+1) {
            string config = line.substr(position + 1);
            int player_num = -1;
            try {
                player_num = boost::lexical_cast<int>(config);
            } catch (std::exception e) {
                throw InvalidConfigurationException();
            }
            if (player_num >= 0 && player_num < 3) {
                this->VBoard_num_of_players = player_num;
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
VGMap VGMapLoader::generateVMap() {
    if(VBoard_num_of_players != -1){
            VGMap vg_map;
            return vg_map;
    }
    else{
        throw BoardConfigurationNotLoaded();
    }
}
