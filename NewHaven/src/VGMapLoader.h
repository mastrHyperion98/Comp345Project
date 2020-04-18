//
// Created by Nizz Wizz on 2020-02-27.
//

#ifndef NEWHAVEN_VGMAPLOADER_H
#define NEWHAVEN_VGMAPLOADER_H
#include <string>
#include "VGMap.h"

class VGMapLoader {
public:
    VGMapLoader();
    VGMapLoader(const VGMapLoader & loader);
    VGMapLoader& operator=(const VGMapLoader & loader);
    ~VGMapLoader();
    bool loadVConfig(std::string filepath);
    VGMap* generateVMap();

private:
    string *name{new string("")};
};

#endif //NEWHAVEN_VGMAPLOADER_H
