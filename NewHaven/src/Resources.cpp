#include "Resources.h"
#include <time.h>
#include <iostream>

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

HarvestTile::HarvestTile() : tileContent{ new ResourceTypes[4] }
{
	generateResources();
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
	if (this == &tile || &tile == nullptr)						//Checking for self-assignment
		return *this;

	delete[] tileContent;					//Delete old data that will be discarded
	tileContent = tile.getTileContent();	//getTileContent returns an array copy
	
	return *this;							//We return the updated object for chain operations
}

void HarvestTile::generateResources()
{
	std::uint_least8_t sheepCount{ 0 }, stoneCount{ 0 }, wheatCount{ 0 }, woodCount{ 0 };	//Keep count of the number of a type on a single tile
	std::srand(time(NULL) + std::rand());	//Different see every execution

	for (std::uint_least8_t i = 0; i < 4; i++)
	{
		switch (std::rand() % 4 + 1)	//Random number between 1 and 4
		{
		case 1:
			sheepCount++;
			/*
			First condition checking that if it's the last iteration, we can't have one of all the other types, otherwise we end up with a tile with 4 different resources
			the second condition makes sure that there are no more than 3 of the current resource, otherwise we'll have a tile full of the same resource.
			Both conditions need to be fullfilled to add the resrouce on the tile.
			*/
			if (((i < 3) || !(stoneCount && wheatCount && woodCount)) && sheepCount <= 3)
			{
				tileContent[i] = ResourceTypes::SHEEP;
			}
			else
			{
				i--;	//If the conditions weren't met, we scrap this iteration and run again hoping to fall on another resource
			}

			break;
		case 2:
			stoneCount++;

			if (((i < 3) || !(sheepCount && wheatCount && woodCount)) && stoneCount <= 3)
			{
				tileContent[i] = ResourceTypes::STONE;
			}
			else
			{
				i--;
			}

			break;
		case 3:
			wheatCount++;

			if (((i < 3) || !(sheepCount && stoneCount && woodCount)) && wheatCount <= 3)
			{
				tileContent[i] = ResourceTypes::WHEAT;
			}
			else
			{
				i--;
			}
			
			break;
		case 4:
			woodCount++;

			if (((i < 3) || !(sheepCount && stoneCount && wheatCount)) && woodCount <= 3)
			{
				tileContent[i] = ResourceTypes::WOOD;
			}
			else
			{
				i--;
			}

			break;
		default:
			i--;
			break;
		}
	}
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
	deckContent{ new HarvestTile[*MAX_DECK_SIZE] }
{}

HarvestDeck::~HarvestDeck()
{
	delete MAX_DECK_SIZE;
	delete deckSize;
	delete[] deckContent;
}

std::uint_least8_t HarvestDeck::getDeckSize() const
{
	return *deckSize;
}

HarvestTile* HarvestDeck::draw() const
{
	if (*deckSize > 0)	//Can only draw when there are still cards
	{
		(*deckSize)--;
		return &deckContent[*deckSize];
	}
	else
	{
		return nullptr;
	}
}

Building::Building(ResourceTypes buildingType, std::uint_least8_t buildingNumber, std::uint_least8_t position) :
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
}

Building& Building::operator=(const Building& building)
{
	if (this == &building)						//Checking for self-assignment
		return *this;
	if(&building != nullptr) {
        *buildingType = *building.buildingType;        //We copy all the member data
        *buildingNumber = *building.buildingNumber;
        *faceUp = *building.faceUp;
    }
	return *this;							//We return the updated object for chain operations
}

bool Building::isFlipped() const
{
	return *faceUp;
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

BuildingDeck::BuildingDeck():
	deckSize{ new std::uint_least8_t(*MAX_DECK_SIZE) },
	deckContent{ new std::vector<Building*> }
{
	deckContent->reserve(*MAX_DECK_SIZE);	//We allocate space without filling it up yet

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
				deckContent->push_back(new Building(buildingType, j));
			}
		}
	}
}

BuildingDeck::~BuildingDeck()
{
	delete MAX_DECK_SIZE;
	delete deckSize;
	delete deckContent;
}

std::uint_least8_t BuildingDeck::getDeckSize() const
{
	return *deckSize;
}

Building* BuildingDeck::draw() const
{
	if (*deckSize > 0)
	{
		(*deckSize)--;
		return deckContent->at(*deckSize);
	}
	else
	{
		return nullptr;
	}
}

Hand::Hand():
	harvestTiles{new std::vector<HarvestTile*>},
	shipment{nullptr},
	buildings{new std::vector<Building*>}
{
	harvestTiles->reserve(2);	//We know a player can only hold 2 harvest tiles
}

Hand::~Hand()
{
	delete harvestTiles;
	delete shipment;
	delete buildings;
}
