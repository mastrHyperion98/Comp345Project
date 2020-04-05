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
        if(header.compare("NEW_HAVEN_VILLAGE_BOARD_LOADER") != 0){
            throw InvalidConfigurationException();
        }
        if(line.length() > position+1) {
            string config = line.substr(position + 1);
            string village_name;
            try {
                village_name=config;
            } catch (std::exception &e) {
                throw InvalidConfigurationException();
            }
                *this->name = village_name;
                return true;
        }
        return false;
    }
    else {
        cerr << "ERROR: File either does not exist or cannot open file" << endl;
        // close the reader before returning
        reader.close();
        throw BoardConfigurationNotLoaded();
    }
}
// create a GBMap, set its configuration and generate the graph before returning it.
VGMap VGMapLoader::generateVMap() {
    if(*name != ""){
            VGMap vg_map{VGMap(*name)};
            return vg_map;
    }
    else{
        throw BoardConfigurationNotLoaded();
    }
}
