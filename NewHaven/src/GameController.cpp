//
// Created by Steven Smith(aka hyperion --> github alias) on 2020-03-27.
// Student ID: 40057065
// Created for: Assingment 2 Concordia W2020 Comp 345 with Dr. Nora
//
// GameController controls the environment and the main game loop of NewHaven
// It uses a singleton design such that essential components such as game decks
// can be assessed anywhere through maintaining only a single instance of GameController.
// Is composed of an aglomeration of functions defined in part 3 and modified to fit the need or
// refactored when the quality of the code was inadequate.

#include "GameController.h"
#include "../Exceptions/UninitializedControllerException.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
// singleton instance
GameController* GameController::current;
// default constructor
GameController::GameController():current_turn_player{new int(0)}, game_settings{nullptr}{
    // singleton only one instance allowed
    delete current;
    current = this;
}

// destructor
GameController::~GameController(){
    delete game_settings;
    delete current_turn_player;
    current = nullptr;
}
// start
// //contains the main loop
void GameController::start(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();
    for(int i = 0; i < 25; i++){
        cout << "\n"; // clear screen
    }
    cout << "STARTING PLAYER HAS ID: " << (*game_settings->players)[*current_turn_player]->getID() << endl;
    while(!hasGameEnded()){
        // PrintGameBoard
        playTurn();
        *current_turn_player = ((*current_turn_player)+1) % game_settings->players->size();
    }
    endGame();
}
// initialize the gameController such that all settings are configured properly
bool GameController::initialize() {
    game_settings = new Setting();
    bool init = game_settings->initSetting();
    if(init)
        *current_turn_player = startingPlayer();
    return init;
}
// find the starting player by comparing their studentID
int GameController::startingPlayer() {
int current_index = 0;
for(int i = 0; i < game_settings->players->size(); i++){
    try {
        int current_id = boost::lexical_cast<int>((*game_settings->players)[current_index]->getID());
        int next_id = boost::lexical_cast<int>((*game_settings->players)[i]->getID());
        if(next_id < current_id)
            current_index = i;
    }
    catch (std::exception &e) {
        cout << "ERROR COULD NOT DETERMINE STARTING PLAYER! ERROR IN STRING-INT CAST ID NOT NUMERIC" << endl;
       // terminate application
        exit(-1);
    }
}
    return current_index;
}
//  playTurn function that executes the turn of the current player and all the user
// interaction needed to complete it
void GameController::playTurn(){
    int pos;
    Player *current = (*game_settings->players)[*current_turn_player];
    bool shipmentPlayed{false};

    if(game_settings == nullptr)
        throw UninitializedControllerException();
    // Print board ID configuration
    cout << "\n***GAME BOARD ID CONFIGURATION***" << endl;
    game_settings->board->printIndexConfiguration();
    cout << "\n***GAME BOARD CONTENT***" << endl;
    game_settings->board->printBoard();
    cout << "Here are your building cards:";
    current->printBuildingCards();
    cout << "\nHere are your Harvest Tiles:";
    current->printHarvestCards();

    if (current->getShipmentTile() != nullptr)
    {
        cout << '\n' << (*game_settings->players)[*current_turn_player]->getID() << " Your turn! What would you like to do? "
                "Enter the number for the move you'd like to make." << endl;

        int tile_option = selectTileOption();
        if(tile_option == 1) {
            pos=current->placeHarvestTile();
            ResourceTrails *trail = game_settings->board->getResourcedGraph(pos);
            game_settings->tracker->computeScore(*trail);
            delete trail;
        }
            // play the shipmentTile
        else if(tile_option == 2){
            pos = playShipmentTile(selectResourceType(), current);
            shipmentPlayed = true;
        }
    }
    else
    {
        pos = current->placeHarvestTile();
        ResourceTrails* trail = game_settings->board->getResourcedGraph(pos);
        game_settings->tracker->computeScore(*trail);
    }

    cout << "\n***UPDATED GAME BOARD CONTENT***" << endl;
    game_settings->board->printBoard();
    // current player builds his village
    current->buildVillage();
    shareTheWealth();
    game_settings->DrawBuilding(*current_turn_player);

    if(shipmentPlayed){
        delete game_settings->board->getHarvestTile(pos)->tileContent;
        game_settings->board->getHarvestTile(pos)->tileContent = original_shipment;
        shipmentPlayed = false;
    }
    else{
        // draw a harvest tile only if one from the players hand was consumed.
        current->drawHarvestTile(game_settings->drawHarvestTile());
    }
}
// end game function
void GameController::endGame(){
// requires part4 and isnt part of what is needed for Part 2 driver
    cout << "\n***GAME OVER!***" << endl;
    scores winners = findWinner();
    // two cases one where ther eis only one winner, or a tie
    string announcement;
    if(winners.size() == 1)
        announcement = "THE WINNER IS: ";

    else
        announcement = "TIE! THE WINNERS ARE:\n";

    cout << announcement;
    for(scores::iterator it = winners.begin(); it != winners.end(); ++it)
        std::cout <<"\n" << it->first->getID() << endl;

    int choice;
    std::cout << "\nWhat do you wish to do, please select from an option below:" << endl;
    std::string prompt = "1\tPlay a new game!"
                         "\n2\tEnd game!"
                         "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }

    if(choice == 1)
        restart();

    else {
        std::cout << "THANK YOU FOR PLAYING NEW HAVEN!" << endl;
        return;
    }
}

// Restart the game
void GameController::restart(){
    delete game_settings;
    initialize();
    start();
}
bool GameController::hasGameEnded(){
    if(game_settings == nullptr)
        throw UninitializedControllerException();

    return game_settings->board->isGameOver();
}
inline int GameController::selectTileOption() {
    int choice;
    std::string prompt = "1\tPlay a Harvest tile from your possession"
                         "\n2\tPlay with your Shipment tile."
                         "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }
    return choice;
}

inline ResourceTypes GameController::selectResourceType() {
    int choice;
    std::string prompt =  "\nWhich resource type would you like?"
                                  "\n\t1 - Sheep"
                                  "\n\t2 - Stone"
                                  "\n\t3 - Wood\n"
                                  "\t4 - Wheat"
                                  "\nChoice: ";
    while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 4){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "This is not a valid move. Select either:" << endl;
    }
    ResourceTypes type;
    if(choice == 1)
        type = ResourceTypes::SHEEP;
    else if(choice == 2)
        type= ResourceTypes::STONE;
    else if(choice == 3)
        type = ResourceTypes::WOOD;
    else
        type = ResourceTypes::WHEAT;
    return type;
}
inline void GameController::setOriginalShipmentTile(Player *player){
    original_shipment = player->getShipmentTile()->tileContent;
}
int GameController::playShipmentTile(ResourceTypes type, Player *player){
    ResourceTypes *tmp_res{new ResourceTypes[4]{type,type,type,type}};
    setOriginalShipmentTile(player);
    // player plays the shipment tile.
    player->getShipmentTile()->tileContent = tmp_res;
    int pos{0};
    POSITION:
    while((cout <<  "position index to place tile: " && !( cin >> pos)) || pos < 0
          || pos >= (25 + (10 * *game_settings->board->CONFIG))){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile index" << endl;
    }
    // later this will be called from the singleton Game Controller
    if(game_settings->board!= nullptr) {
        if(game_settings->board->placeHarvestTile(pos, player->getShipmentTile())){
            // print new board config
            player->setShipmentPlayed();
            // compute resourceTracker using compies
            game_settings->tracker->computeScore(*game_settings->board->getResourcedGraph(pos));
            // once resource_score is calculated we flip the tile over
        } else{
            cout << "Position Index is invalid. It has already been played!"<<endl;
            goto POSITION;
        }
    }
    return pos;
}
/*
 * Share the wealth function. We decided to alter the structure of the player slighty and
 * move the resourceTracker object off the players. It is dependent solely on the resourceTrail generated by
 * the game board. As such maintaining up to four instance of the object (1 per player) seemed inefficient
 * and a waste of space. A single resourceTracker facility exists within the Settings file (Part 1)
 * and is used to service all the players. We believe this to be much more efficient.
 *
 * This has been changed as the A1 requirements vaguely talked about a resourceTracker() held by the
 * player. This was poorly described and lack any indication as to its usage within the player class.
 */
void GameController::shareTheWealth(){
    int player_index{static_cast<int>((*current_turn_player + 1) % game_settings->players->size())};
    do{
        // print out the available resources
        // prompt user to action
        cout << "\nLeftover resources:" << endl;
        game_settings->tracker->printScore();
        cout << "\nHere are your building cards:";
        (*game_settings->players)[player_index]->printBuildingCards();
        string prompt = '\n' + (*game_settings->players)[player_index]->getID() + " Would you like to use the leftover resources to erect a building in your village?"
                        "\n1\tErect a building.\n2\tPass\nChoice: ";
        int choice{0};
        while((cout <<  prompt && !(cin >> choice))||choice < 1 || choice > 2){
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "This is not a valid move. Select either 1 or 2:" << endl;
        }
        // call build village for that user
        if(choice == 1){
            (*game_settings->players)[player_index]->buildVillage();
        }

        player_index = ++player_index % game_settings->players->size();

    }while(player_index != *current_turn_player && !game_settings->tracker->isEmpty());
}
// this will need to be tested
scores GameController::findWinner(){
    vector<Player*> *players = game_settings->players;
    // now that we have the list of players we want to create a map of players and points
    scores player_scores;
    // iterate through list of players
    for(std::vector<Player*>::iterator it{players->begin()}; it != players->end(); ++it){
        int score{(*it)->calculateScore()};
        cout << "\nPlayer: " << (*it)->getID() << " has " << score << " colonists" << endl;
         // add the entry to the map
        player_scores.insert(entry(*it,score));
    }
    // now we need to traverse the map and find the max value
    int current_max{0};
    int max_score{0};
    max_score = player_scores[(*players)[current_max]];
    for(int i{0}; i < player_scores.size(); i++){
        if(player_scores[(*players)[current_max]] < player_scores[(*players)[i]]) {
            current_max = i;
            max_score = player_scores[(*players)[i]];
        }
    }
    // a bit more work needs to be done now we remove all those that are not equal to max
    auto it = player_scores.begin();
    while(it != player_scores.end()){
        if(it->second != max_score)
           it= player_scores.erase(it);
        else
            ++it;
    }
    // now the map should contain only the list of players that have the max score only
    // if there is only one entry it is the sole max so return it
    if(player_scores.size() == 1)
        return player_scores;
        // otherwise try to break the tie by counting number of empty spaces left on village board
    else{

        // update the map using the number of buildings space left
        it = player_scores.begin();
        while(it != player_scores.end()){
            int num_spaces_empty =  it->first->getVillage().getNumUnplayed();
            it->second = num_spaces_empty;
            cout << "\nPlayer: " << it->first->getID() << " has " << num_spaces_empty << " empty spaces on their board" << endl;
            it++;
        }
        // now we find that lowest number and repeat our previous loops
        int current_min{0};
        int min_score{player_scores[(*players)[current_max]]};
        for(int i{0}; i < player_scores.size(); i++){
            if(player_scores[(*players)[current_min]] > player_scores[(*players)[i]]) {
                current_min = i;
                min_score = player_scores[(*players)[i]];
            }
        }
        // a bit more work needs to be done now we remove all those that are not equal to max
        it = player_scores.begin();
        while(it != player_scores.end()){
            if( it->second != min_score) {
               it= player_scores.erase(it);
            }
            else
                ++it;
        }
        if(player_scores.size() == 1)
            return player_scores;
            // if more than one player still remains than we check their hands
            //  If  still  tied,  then  the player  with  the  least  buildings  leftover wins so repeat again
        else{
            it = player_scores.begin();
            while(it != player_scores.end()){
                int hand_size = it->first->getHand().buildings->size();
                it->second = hand_size;
                cout << "\nPlayer: " << it->first->getID() << " has " << hand_size << " buildings left in their hand" << endl;
                it++;
            }
            current_min=0;
            min_score=player_scores[(*players)[current_max]];
            for(int i{0}; i < player_scores.size(); i++){
                if(player_scores[(*players)[current_min]] > player_scores[(*players)[i]]) {
                    current_min = i;
                    min_score = player_scores[(*players)[i]];
                }
            }
            // a bit more work needs to be done now we remove all those that are not equal to max
            it = player_scores.begin();
            while(it != player_scores.end()){
                if(it->second != min_score)
                    it = player_scores.erase(it);
                else
                    ++it;
            }
            // now regardless of result return winners
            return player_scores;
        }
    }
}