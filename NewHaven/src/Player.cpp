#include "Player.h"
#include "GBMap.h"
Player::Player(){
    village = new VGMap();
    resource_score = new ResourceScore();
    vb_score = new ScoreCalculator();
    my_hand = new Hand();
}

Player::Player(const Player &player) {
    village = new VGMap(*player.village);
    resource_score = new ResourceScore(*player.resource_score);
    vb_score = new ScoreCalculator(*player.vb_score);
    my_hand = new Hand(*player.my_hand);
}

Player::~Player(){
    delete village;
    delete resource_score;
    delete vb_score;
    delete my_hand;
}

Player& Player::operator=(const Player &player) {
    // nullptr and self assignment guard
    if(&player == this || &player == nullptr)
        return *this;
    else{
        // use assignment operator overload
        *village = *player.village;
        *resource_score = *player.resource_score;
        *vb_score = *player.vb_score;
        *my_hand = *player.my_hand;
    }
    return *this;
}
// I'm assuming it just wants to return the resource_tracker
ResourceScore Player::resourceTracker() {
    // return a copy of the resource score;
    return *resource_score;
}

void Player::calculateResources(ResourceTrails trail) {
    resource_score->computeScore(trail);
}

bool Player::buildVillage(){

    SELECT:
    for(int i = 0; i < my_hand->buildings->size(); i++){
        cout << "building index: " << i << " type\t" <<  (*my_hand->buildings)[i]->getBuildingType() << " cost: "
        << static_cast<int>((*my_hand->buildings)[i]->getBuildingNumber()) << endl;
    }

    int index;
    int pos;
    cout <<  "Building index to play: ";
    cin >> index;
    POSITION:
    cout <<  "position index to place tile: ";
    cin >> pos;

    if(index < 0 || index > my_hand->buildings->size()){
        cout << "Incorrect Index. There are no building at that index. Please try again." << endl;
        goto SELECT;
    }
    std::uint_least16_t cost = 0;
    if((*my_hand->buildings)[index]->isFlipped())
        cost = (*my_hand->buildings)[index]->getBuildingNumber();
    else
        cost = village->getPositionCost(pos);

    if(cost == -1){
        cout << "Incorrect Position. Please try again" << endl;
        goto POSITION;
    }
    Building building = *(*my_hand->buildings)[index];
    ResourceTypes type=building.getBuildingType();
    if(resource_score->hasResources(type, cost)) {
        if(village->setBuilding(pos, &building)) {
            resource_score->consumeResources(type, cost);
            my_hand->buildings->erase(my_hand->buildings->begin() + index);
            return true;
        }
        else{
            cout << "ERROR cannot play resource" << endl;
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
    TILE:
    cout <<  "Tile index to place: ";
    cin >> index_tile;

    if(index_tile < 0 || index_tile >= my_hand->harvestTiles->size()) {
        cout << "That is not a valid tile" << endl;
        goto TILE;

    }
    POSITION:
    cout <<  "position index to place tile: ";
    cin >> pos;

    // later this will be called from the singleton Game Controller
    if(GBMap::current_map != nullptr) {
        if(GBMap::current_map->placeHarvestTile(pos, *(*my_hand->harvestTiles)[index_tile])) {
            my_hand->harvestTiles->erase(my_hand->harvestTiles->begin() + index_tile);
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
void Player::drawBuilding(Building& building) {
    my_hand->buildings->push_back(&building);
}
/*
 * NON FINAL IMPLEMENTATION -- IDEALLY WE WANT TO DRAW DIRECTLY FROM THE HARVEST DECK WITHOUT HAVING TO PASS ARGUMENTS
 * HarvestDeck has to be static within the Game Controller
 */
void Player::drawHarvestTile(HarvestTile& tile) {
    my_hand->harvestTiles->push_back(&tile);
}

