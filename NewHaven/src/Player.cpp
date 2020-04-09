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

    bool playAgain{true};
    while(playAgain) {
        village->PrintGraph();
        cout << "Available resources:" << endl;
        GameController::current->game_settings->tracker->printScore();
        printBuildingCards();

        SELECT_BUILDING:
        int index;
        bool valid = false;
        do {
            cout << "\nBuilding index to play (0 to skip): ";
            cin >> index;
            if (cin.good()) {
                valid = true;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input; please re-enter." << endl;
            }
        } while (index < 0 || index > my_hand->buildings->size() + 1 || !valid);

        if (index == 0)
            return false;

        index--;

        int pos;
        bool pValid = false;
        do {
            cout << "position index to place tile: ";
            cin >> pos;
            if (cin.good()) {
                pValid = true;
            } else {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid position; please re-enter" << endl;
            }
        } while (!pValid || pos < 0 || pos >= 30);

        Building *building = (*my_hand->buildings)[index];
        ResourceTypes type = building->getBuildingType();

        int flipped;

        cout << "\nDo you want to place the building face up or face down? (0 for face up or 1 for face down): ";
        cin >> flipped;
        while (cin.fail() || flipped > 1 || flipped < 0) {
            cout << "\n Invalid input. Enter number 0 or 1. (0 for face up or 1 for face down): "
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
        if (GameController::current->game_settings->tracker->hasResources(type, cost)) {
            if (village->setBuilding(pos, building)) {
                GameController::current->game_settings->tracker->consumeResources(type, cost);
                my_hand->buildings->erase(my_hand->buildings->begin() + index);

                int restart{0};
                std::string prompt = "\nSelect one of the options below: "
                                     "\n1\tPlay another building from your possession"
                                     "\n2\tDone building."
                                     "\nChoice: ";
                while ((cout << prompt && !(cin >> restart)) || restart < 1 || restart > 2) {
                    cin.clear(); // reset failbit
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "This is not a valid move. Try again!:" << endl;
                }
                playAgain = restart == 1;
            } else {
                cin.clear(); // reset failbit
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "ERROR cannot play building in that position." << endl;
                goto SELECT_BUILDING;
            }
        } else {
            cin.clear(); // reset failbit
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Cannot play building: Insufficient resources" << endl;
            goto SELECT_BUILDING;
        }
    }
    return true;
}

int Player::placeHarvestTile() {

    int index_tile;
    int pos;

    TILE_SELECT:
    while((cout <<  "\nTile index to place: " && !(cin >> index_tile))||index_tile < 1 || index_tile >= my_hand->harvestTiles->size() + 1){
          cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nThat is not a valid tile index" << endl;
    }
    int choice_rot{0};
    cout << "\nHere is a combination of rotations possible for your tile:\n";
    // show possible tile positions
    HarvestTile * tile = (*my_hand->harvestTiles)[index_tile-1];
    ResourceTypes *types = tile->getTileContent();
    // position 1 --> default
    cout << "\n1:\t" <<types[0] << '\t' <<types[1] << endl;
    cout << "  \t" << types[3] << '\t' << types[2] << endl << endl;
    delete types;
    // position 2 -->
    tile->rotateTileClockwise();
    types = tile->getTileContent();;
    cout << "2:\t" <<types[0] << '\t' <<types[1] << endl;
    cout << "  \t" << types[3] << '\t' << types[2] << endl << endl;
    delete types;
    // position 3
    tile->rotateTileClockwise();
    types = tile->getTileContent();;
    cout << "3:\t" << types[0] << '\t' <<types[1] << endl;
    cout << "  \t" << types[3] << '\t' << types[2] << endl << endl;
    delete types;
    // position 4
    tile->rotateTileClockwise();
    types = tile->getTileContent();;
    cout << "4:\t" << types[0] << '\t' <<types[1] << endl;
    cout << "  \t" << types[3] << '\t' << types[2] << endl << endl;
    delete types;

    while( (cout << "Choice: " && !(cin >> choice_rot)) || choice_rot < 0 || choice_rot > 4){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile rotation" << endl;
    }
    if(choice_rot == 0) {
        cout << "\nHere are your Harvest Tiles:";
        my_hand->printHarvestTiles();
        goto TILE_SELECT;
    }

    else{
        for(int i = 0; i < choice_rot; i++)
            tile->rotateTileClockwise();
    }

    POSITION:
    while((cout <<  "Position index to place tile: " && !( cin >> pos)) || pos < 0
    || pos >= (25 + (10 * *GameController::current->game_settings->board->CONFIG))){
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "That is not a valid tile index" << endl;
    }

    // later this will be called from the singleton Game Controller
    if(GameController::current->game_settings->board!= nullptr) {
        if(GameController::current->game_settings->board->placeHarvestTile(pos, tile)) {
            my_hand->harvestTiles->erase(my_hand->harvestTiles->begin() + (index_tile - 1));
            return pos;
        } else{
            cout << "Position Index is invalid. It has already been played!"<<endl;
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
    my_hand->shipment = nullptr;
}

void Player::printHarvestCards()
{
    my_hand->printHarvestTiles();
}

void Player::printBuildingCards()
{
    my_hand->printBuildings();
}

int Player::calculateScore() const{
    return vb_score->getScore(*village);
}

VGMap Player::getVillage() const {
    // returns a copy but that is 100% fine
    return *village;
}

Hand Player::getHand() const{
    return *my_hand;
}