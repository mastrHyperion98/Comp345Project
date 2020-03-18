//
// Created by hyperion on 2020-03-17.
//
#include "Setting.h"
#include "iostream"
HarvestDeck* Setting::h_deck;
BuildingDeck* Setting::b_deck;
GBMap* Setting::board;
vector<Player>* Setting::players;

Setting::Setting(){
    h_deck = nullptr;
    b_deck = nullptr;
    board = nullptr;
    players = nullptr;
}

Setting::~Setting() {
    delete h_deck;
    delete b_deck;
    delete board;
    delete players;
}

void Setting::setupPlayers(const int numberOfPlayers) {
    std::cout << "CREATING " << numberOfPlayers << " PLAYERS!" << endl;
    vector<Player> player_list;
    for(int i = 0; i < numberOfPlayers;i++){
        Player player;
        player_list.push_back(player);
    }
    players = new vector<Player>(player_list);
    std::cout << numberOfPlayers << " PLAYERS HAVE BEEN SUCCESFULLY CREATED!" << endl;
}