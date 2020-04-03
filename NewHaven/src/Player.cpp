#include "Setting.h"
#include "GameController.h"

Player::Player(string id): id{new string(id)}, village{nullptr}, vb_score{new ScoreCalculator()}, my_hand{new Hand()}{

}

Player::Player(const Player &player): id{new string(*player.id)}, vb_score{new ScoreCalculator(*player.vb_score)},  my_hand{new Hand(*player.my_hand)}{
    if (player.village != nullptr)
        village = new VGMap(*player.village);
    else
        village = nullptr;
}

Player::~Player(){
    delete village;
    delete vb_score;
    delete my_hand;
    delete id;
}

Player& Player::operator=(const Player &player) {
    // nullptr and self assignment guard
    if(&player == this || &player == nullptr)
        return *this;
    else{
        // use assignment operator overload
        *village = *player.village;
        *vb_score = *player.vb_score;
        *my_hand = *player.my_hand;
        *id = *player.id;
    }
    return *this;
}


void Player::calculateResources(ResourceTrails trail) {
    GameController::current->game_settings->tracker->computeScore(trail);
}

bool Player::buildVillage(){
    for(int i = 0; i < my_hand->buildings->size(); i++){
        cout << "building index: " << i << " type\t" <<  (*my_hand->buildings)[i]->getBuildingType() << " cost: "
        << static_cast<int>((*my_hand->buildings)[i]->getBuildingNumber()) << endl;
    }

    int index;
    bool valid= false;
    do {cout <<  "Building index to play: ";
        cin >> index;
        if(cin.good()){
            valid = true;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid input; please re-enter." << endl;
        }
    }  while(index < 0 || index > my_hand->buildings->size() || !valid);


    int pos;
    bool pValid = false;
    do {cout<<"position index to place tile: ";
            cin >> pos;
            if (cin.good()) {
                pValid = true;
            }
            else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid pos; please re-enter" << endl;
            }
        } while(!pValid || pos < 0 || pos >= 30);

    Building building = *(*my_hand->buildings)[index];
    ResourceTypes type=building.getBuildingType();

    int flipped;

    cout << "Do you want to place the building face up or face down? (0 for face up or 1 for face down): " << endl;
    cin >> flipped;
    while(cin.fail() || flipped > 1 || flipped < 0){
            cout << "Do you want to place the building face up or face down? (0 for face up or 1 for face down): "
                 << endl;
            cin.clear();
            std::cin.ignore(256, '\n');
            cin >> flipped;
    }

    std::uint_least16_t cost = 0;

    if (flipped == 0) {
        (*my_hand->buildings)[index]->isFlipped();
        cost = (*my_hand->buildings)[index]->getBuildingNumber();
    }
    // just need to assign cost
    else if (flipped == 1) {
        (*my_hand->buildings)[index]->flipCard();
        cost = village->getPositionCost(pos);
    }

//    Building building = *(*my_hand->buildings)[index];
//    ResourceTypes type=building.getBuildingType();
    if(GameController::current->game_settings->tracker->hasResources(type, cost)) {
        if(village->setBuilding(pos, &building)) {
            GameController::current->game_settings->tracker->consumeResources(type, cost);
            my_hand->buildings->erase(my_hand->buildings->begin() + index);
            return true;
        }
        else{
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "ERROR cannot play building in that position. Costs do not match!" << endl;
        }
    }
    else{
        cout << "Cannot play building: Insufficient resources" << endl;
    }
    return false;
}

int Player::placeHarvestTile() {

    // print hand
    for(int i = 0; i < my_hand->harvestTiles->size(); i++){
        cout << "tile index: " << i << " content\t" <<  (*my_hand->harvestTiles)[i]->getTileContent()[0] << " , "
        << (*my_hand->harvestTiles)[i]->getTileContent()[1] << " , "<< (*my_hand->harvestTiles)[i]->getTileContent()[2]
        << " , " << (*my_hand->harvestTiles)[i]->getTileContent()[3] << endl;
    }

    int index_tile;
    int pos;

    while((cout <<  "Tile index to place: " && !(cin >> index_tile))||index_tile < 0 || index_tile >= my_hand->harvestTiles->size()){
          cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile index" << endl;
    }

    POSITION:
    while((cout <<  "position index to place tile: " && !( cin >> pos)) || pos < 0
    || pos >= (25 + (10 * *GameController::current->game_settings->board->CONFIG))){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile index" << endl;
    }

    // later this will be called from the singleton Game Controller
    if(GameController::current->game_settings->board!= nullptr) {
        if(GameController::current->game_settings->board->placeHarvestTile(pos, (*my_hand->harvestTiles)[index_tile])) {
            my_hand->harvestTiles->erase(my_hand->harvestTiles->begin() + index_tile);
            return pos;
        } else{
            cout << "Position Index is invalid. It has already been played!"<<endl;
            goto POSITION;
        }
    }
    return -1;
}

// Used to play the last tile on hand, which is done immediately after drawing the Shipment Tile.
int Player::placeShipmentTile() {
    int pos;

    POSITION:
    cout <<  "position index to place tile: ";
    cin >> pos;

    // later this will be called from the singleton Game Controller
    if(GameController::current->game_settings->board != nullptr) {
        if(GameController::current->game_settings->board->placeHarvestTile(pos, (*my_hand->harvestTiles).back())) {
            my_hand->harvestTiles->erase(my_hand->harvestTiles->end());
            return pos;
        }
        else{
            cout << "This position is incorrect. Please select another position" << endl;
            goto POSITION;
        }
    }
    return -1;
}

/*
 * NON FINAL IMPLEMENTATION:
 *
 * For drawBuilding we need to draw for the number of Resource Marker on the 0 (zero) space of the Resource Track.
 * However, since we havent decided or discussed user inputs yet then for the moment I'm leaving this as it is.
 * Since we need to process whether the user will draw from the board or the deck, in the case where they draw more than
 * one.
 */
void Player::drawBuilding(Building* building) {
    my_hand->buildings->push_back(building);
}
/*
 * NON FINAL IMPLEMENTATION -- IDEALLY WE WANT TO DRAW DIRECTLY FROM THE HARVEST DECK WITHOUT HAVING TO PASS ARGUMENTS
 * HarvestDeck has to be static within the Game Controller
 */
void Player::drawHarvestTile(HarvestTile* tile) {
    my_hand->harvestTiles->push_back(tile);
}

void Player::drawBuildingPool(Building* building)
{
    my_hand->buildings->push_back(building);
}


void Player::setShipmentTile(HarvestTile* tile){
    if(my_hand->shipment == nullptr)
        my_hand->shipment = tile;
}

HarvestTile* Player::getShipmentTile() {
    return my_hand->shipment;
}

void Player::setVillage(VGMap v_map) {
    village = new VGMap(v_map);
}

string Player::getID(){
    return *id;
}

void Player::setShipmentPlayed(){
    *my_hand->isShipmentPlayed = true;
}

bool Player::isShipmentPlayed(){
return *my_hand->isShipmentPlayed;
}