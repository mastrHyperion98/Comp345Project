#include "Resources.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

std::ostream& operator<<(std::ostream& output, const ResourceTypes& resource)
{
	/*
	Case by case, we print the proper string for each enum type
	*/
	switch (resource)
	{
	case ResourceTypes::SHEEP:
		output << "Sheep";
		return output;
	case ResourceTypes::STONE:
		output << "Stone";
		return output;
	case ResourceTypes::WHEAT:
		output << "Wheat";
		return output;
	case ResourceTypes::WOOD:
		output << "Wood";
		return output;
	default:
		output << "Resource Type Error";
		return output;
	}
}

HarvestTile::HarvestTile(ResourceTypes* tileContent) : tileContent{ new ResourceTypes[4] }
{
	for (std::uint_fast8_t i = 0; i < 4; i++)
	{
		this->tileContent[i] = tileContent[i];
	}
}

HarvestTile::HarvestTile(const HarvestTile& tile) : tileContent{ new ResourceTypes[4] }
{
    // reassign the values by using pass-by value
	tileContent[0] = tile.tileContent[0];
	tileContent[1] = tile.tileContent[1];
	tileContent[2] = tile.tileContent[2];
	tileContent[3] = tile.tileContent[3];
}

HarvestTile::~HarvestTile()
{
	delete[] tileContent;
}

HarvestTile& HarvestTile::operator=(const HarvestTile& tile)
{
	if (this == &tile)						//Checking for self-assignment
		return *this;

	delete[] tileContent;					//Delete old data that will be discarded
	tileContent = tile.getTileContent();	//getTileContent returns an array copy
	
	return *this;							//We return the updated object for chain operations
}

void HarvestTile::rotateTileClockwise()
{
	ResourceTypes _temp{ tileContent[3] };
	/*
	We move the content of the array clockwise: index 0->1->2->3->0
	*/
	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		tileContent[3-i] = tileContent[2-i];	//3->2->1->0->_temp(which is 3), 
	}
	
	tileContent[0] = _temp;
}

void HarvestTile::rotateTileCounterClockwise()
{
	ResourceTypes _temp{ tileContent[0] };

	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		tileContent[i] = tileContent[i+1];	//0->1->2->3->_temp(which is 0)
	}

	tileContent[3] = _temp;
}

ResourceTypes* HarvestTile::getTileContent() const
{
	ResourceTypes* tileContent{ new ResourceTypes[4] };

	for (std::int_fast8_t i = 0; i < 4; i++)
	{
		tileContent[i] = this->tileContent[i];	//Copy array
	}

	return tileContent;
}

HarvestDeck::HarvestDeck():
	deckSize{ new std::uint_least8_t(*MAX_DECK_SIZE) },
	deckContent{ new std::vector<HarvestTile*> }
{
	deckContent->reserve(*MAX_DECK_SIZE + 1);	 //+1 for the card swapping during draw
	/*
	In VS, the file path is relative to the build directory, not the source file directory.
	The build directory is represented where the debug condition is true.
	*/
#ifdef _DEBUG
	std::ifstream inFile("../../../config/HarvestTiles.config");

#else
	std::ifstream inFile("../config/HarvestTiles.config");

#endif // DEBUG

	if (!inFile)
	{
		std::cerr << "\n../config/HarvestTiles.config was not found or could not be opened for reading.\n";
		exit(1);
	}

	std::string resourceToken[4];						//To store file line data
	ResourceTypes* resource{ new ResourceTypes[4] };	//Resource array to construct Harvest Tile with

	inFile.ignore(256, '\n');	//We skip the first line

	while (inFile)		//While we didn't reach the end of the file yet
	{
		std::getline(inFile, resourceToken[0], '\t');	//Get the fours elements of the line
		std::getline(inFile, resourceToken[1], '\t');
		std::getline(inFile, resourceToken[2], '\t');
		std::getline(inFile, resourceToken[3], '\n');	//The last element is delimited by a new line

		for (std::uint_fast8_t i = 0; i < 4; i++)		//For all four resources in the line
		{
			switch (resourceToken[i].at(0) - resourceToken[i].at(1)) //We take the difference between the two characters composing the resource
			{	//sh:11, st:-1, wd:19, wt:3
			case 11:
				resource[i] = ResourceTypes::SHEEP;
				break;
			case -1:
				resource[i] = ResourceTypes::STONE;
				break;
			case 19:
				resource[i] = ResourceTypes::WOOD;
				break;
			case 3:
				resource[i] = ResourceTypes::WHEAT;
				break;
			default:
				break;
			}
		}

		deckContent->push_back(new HarvestTile(resource));	//We push the harvest tile with the specified resources inside the deck
	}

	delete[] resource;		//We delete the temporary variable used for constructing Harvest Tiles
}

HarvestDeck::~HarvestDeck()
{
	delete MAX_DECK_SIZE;
	delete deckSize;
	for(int i = 0; i < deckContent->size(); i++)
	    delete (*deckContent)[i];
	delete deckContent;
}

std::uint_least8_t HarvestDeck::getDeckSize() const
{
	return *deckSize;
}

HarvestTile* HarvestDeck::draw()
{
	std::srand(time(NULL) + std::rand());	//Different seed every execution

	if (*deckSize > 0)	//Can only draw when there are still cards
	{
		int cardIndex = std::rand() % *deckSize;
		HarvestTile* pickedCard{ deckContent->at(cardIndex) };

		deckContent->push_back(pickedCard);
		deckContent->erase(deckContent->begin() + cardIndex);
		(*deckSize)--;

		return pickedCard;
	}
	else
	{
		return nullptr;
	}
}

Building::Building(ResourceTypes buildingType, std::uint_least8_t buildingNumber) :
	buildingType{ new ResourceTypes(buildingType) },
	buildingNumber{ new std::uint_least8_t(buildingNumber) },
	faceUp{ new bool(true) }
{}

Building::Building(const Building &building) {
    buildingType = new ResourceTypes(*building.buildingType);
    buildingNumber = new std::uint_least8_t(*building.buildingNumber);
    faceUp = new bool(*building.faceUp);
}
Building::~Building()
{
	delete buildingType;
	delete buildingNumber;
	delete faceUp;
}

Building& Building::operator=(const Building& building)
{
	if (this == &building)						//Checking for self-assignment
		return *this;

	*buildingType = *building.buildingType;		//We copy all the member data
	*buildingNumber = *building.buildingNumber;
	*faceUp = *building.faceUp;

	return *this;							//We return the updated object for chain operations
}

bool Building::isFlipped() const
{
	return !*faceUp;
}

ResourceTypes Building::getBuildingType() const
{
	return *buildingType;
}

std::uint_least8_t Building::getBuildingNumber() const
{
	return *buildingNumber;
}

bool Building::flipCard()
{
	*faceUp = !*faceUp;
	return *faceUp;
}

BuildingDeck::BuildingDeck() :
	deckSize{ new std::uint_least8_t(*MAX_DECK_SIZE) },
	deckContent{ new std::vector<Building*> },
	buildingPoolContent{ new std::vector<Building*> }
{
	deckContent->reserve(*MAX_DECK_SIZE + 1);	//We allocate space without filling it up yet, +1 for the card swapping during draw
	buildingPoolContent->reserve(5);

	ResourceTypes buildingType;

	for (std::uint_fast16_t i = 0; i < 4; i++)	//BuildingType will be a different resource every iteration
	{
		switch (i)
		{
		case 0:
			buildingType = ResourceTypes::SHEEP;
			break;
		case 1:
			buildingType = ResourceTypes::STONE;
			break;
		case 2:
			buildingType = ResourceTypes::WHEAT;
			break;
		case 3:
			buildingType = ResourceTypes::WOOD;
			break;
		default:
			break;
		}
		/*
		We create a building with the same number 6 times before incrementing it all the way to 6. The building type stays the same.
		We create 36 building cards of the same resource and add it to the deckContent vector
		*/
		for (std::uint_fast8_t j = 0; j < 6; j++)
		{
			for (std::uint_fast8_t k = 0; k < 6; k++)
			{
				deckContent->push_back(new Building(buildingType, j+1));
			}
		}
	}

	fillBuildingPool();
}

BuildingDeck::~BuildingDeck()
{
	delete MAX_DECK_SIZE;
	delete deckSize;
    for(int i = 0; i < deckContent->size(); i++)
        delete (*deckContent)[i];
	delete deckContent;
	delete buildingPoolContent;
}

std::uint_least8_t BuildingDeck::getDeckSize() const
{
	return *deckSize;
}

std::uint_least8_t BuildingDeck::getBuildingPoolSize() const
{
	return buildingPoolContent->size();
}
void BuildingDeck::printBuildingPool() {
    std::cout << "\n***Building Pool Content***\n" << std::endl;
    for(int i = 0; i < buildingPoolContent->size(); i++){
        std::cout << "building index: " << i +1<< " type\t" <<  (* buildingPoolContent)[i]->getBuildingType() << "\tcost: "
             << static_cast<int>((* buildingPoolContent)[i]->getBuildingNumber()) << std::endl;
    }
}
Building* BuildingDeck::draw()
{
	std::srand(time(NULL) + std::rand());	//Different seed every execution

	if (*deckSize > 0)	//Can only draw when there are still cards
	{
		int cardIndex = std::rand() % *deckSize;
		Building* pickedCard{ deckContent->at(cardIndex) };

		deckContent->push_back(pickedCard);
		deckContent->erase(deckContent->begin() + cardIndex);
		(*deckSize)--;

		return pickedCard;
	}
	else
	{
		return nullptr;
	}
}

Building* BuildingDeck::buildingPoolDraw(const std::uint_least8_t& index)
{
	if (buildingPoolContent->size() && index >= 0 && index < buildingPoolContent->size())
	{
		Building* pickedCard{ buildingPoolContent->at(index) };
		buildingPoolContent->erase(buildingPoolContent->begin() + index);

		return pickedCard;
	}
	else
	{
		return nullptr;
	}
}

void BuildingDeck::fillBuildingPool()
{
	while (buildingPoolContent->size() < 5)
	{
		buildingPoolContent->push_back(draw());
	}
}

Hand::Hand():
	harvestTiles{new std::vector<HarvestTile*>},
	shipment{nullptr},
	buildings{new std::vector<Building*>}
{
	harvestTiles->reserve(2);	//We know a player can only hold 2 harvest tiles
}

Hand::Hand(const Hand &hand):harvestTiles{new std::vector<HarvestTile*>(*hand.harvestTiles)},
shipment{hand.shipment},
buildings{new std::vector<Building*>(*hand.buildings)}
{
    harvestTiles->reserve(2);	//We know a player can only hold 2 harvest tiles
}

Hand& Hand::operator=(const Hand &hand) {
    if(this == &hand)
        return *this;

    *harvestTiles = *hand.harvestTiles;
    shipment = hand.shipment;
    *buildings = *hand.buildings;
    return *this;
}
Hand::~Hand()
{
    // do not delete the tiles references they will be deleted by the decks
	delete harvestTiles;
	//delete shipment;
	delete buildings;
}

void Hand::printHarvestTiles()
{
	std::cout << '\n';

	for (std::uint_fast8_t j{ 0 }; j < 3;)
	{
		for (std::uint_fast16_t i{ 0 }; i < harvestTiles->size(); ++i)
		{
			if (j == 0)
				std::cout << i + 1 << ".\t" << (*harvestTiles)[i]->tileContent[j] << '\t' << (*harvestTiles)[i]->tileContent[j + 1] << "\t\t";
			else
				std::cout << '\t' << (*harvestTiles)[i]->tileContent[j + 1] << '\t' << (*harvestTiles)[i]->tileContent[j] << "\t\t";
		}

		std::cout << '\n';

		j += 2;
	}
}

void Hand::printBuildings()
{
	for (int i = 0; i < buildings->size(); i++) {
		std::cout << "\nbuilding index: " << i + 1 << " type\t" << (*buildings)[i]->getBuildingType() << "\tcost: "
			<< static_cast<int>((*buildings)[i]->getBuildingNumber()) << '\n';
	}
}
