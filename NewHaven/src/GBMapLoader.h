//
// Created by Steven Smith on 2020-02-20.
// Created for: Concordia W 2020 Comp 345
// Header file for the GBMap Loader defines the signature for the methods that will be used to read a file
//

#ifndef NEWHAVEN_GBMAPLOADER_H
#define NEWHAVEN_GBMAPLOADER_H
#include <string>
#include "GBMap.h"
class GBMapLoader {
public:
    bool loadConfig(std::string filepath);
    GBMap* generateMap();

private:
    int game_board_configuration = -1;

};


#endif //NEWHAVEN_GBMAPLOADER_H
