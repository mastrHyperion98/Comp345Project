#include <iostream>
#include "source/GBMap.h"

int main() {
    GBMap *map = new GBMap();
    map->SetBoardConfig(0);
    map->GenerateGraph();
    map->CreateUpperLowerField();
    map->CreateLeftRightField();
    map->PrintGraph();
    std::cout << "Print Connected Components";
    map->PrintConnectedGraph();
    return 0;
}
