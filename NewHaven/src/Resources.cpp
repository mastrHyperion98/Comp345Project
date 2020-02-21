#include "Resources.h"
#include <time.h>

std::ostream& operator<<(std::ostream& output, const ResourceTypes resource)
{
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

HarvestTile::HarvestTile() : tileContent{ new ResourceTypes[4] }, position{ new std::uint_least8_t() }
{
	generateResources();
}

HarvestTile::~HarvestTile()
{
	delete position;
	delete[] tileContent;
}

void HarvestTile::generateResources()
{
	std::uint_least8_t sheepCount{ 0 }, stoneCount{ 0 }, wheatCount{ 0 }, woodCount{ 0 };
	std::srand(time(NULL) + std::rand());

	for (std::uint_least8_t i = 0; i < 4; i++)
	{
		switch (std::rand() % 4 + 1)
		{
		case 1:
			sheepCount++;

			if (((i < 3) || !(stoneCount && wheatCount && woodCount)) && sheepCount <= 3)
			{
				tileContent[i] = ResourceTypes::SHEEP;
			}
			else
			{
				i--;
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
	
	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		tileContent[3-i] = tileContent[2-i];
	}
	
	tileContent[0] = _temp;
}

void HarvestTile::rotateTileCounterClockwise()
{
	ResourceTypes _temp{ tileContent[0] };

	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		tileContent[i] = tileContent[i+1];
	}

	tileContent[3] = _temp;
}

ResourceTypes* HarvestTile::getTileContent() const
{
	ResourceTypes* tileContent{ new ResourceTypes[4] };

	for (std::int_fast8_t i = 0; i < 4; i++)
	{
		tileContent[i] = this->tileContent[i];
	}

	return tileContent;
}

std::uint_least8_t HarvestTile::getPosition() const
{
	return *position;
}

HarvestDeck::HarvestDeck(std::uint_least8_t deckSize):
	MAX_DECK_SIZE{ new std::uint_least8_t(deckSize) },
	deckSize{ new std::uint_least8_t(deckSize) },
	deckContent{ new HarvestTile[deckSize] }
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
	if (*deckSize > 0)
	{
		(*deckSize)--;
		return &deckContent[*deckSize];
	}
	else
	{
		return nullptr;
	}
}

Building::Building(ResourceTypes buildingType, std::uint_least8_t buildingNumber, std::uint_least8_t position):
	buildingType{new ResourceTypes(buildingType)},
	buildingNumber{new std::uint_least8_t(buildingNumber)},
	position{new std::uint_least8_t(position)}
{}

Building::~Building()
{
	delete buildingType;
	delete buildingNumber;
	delete position;
}

ResourceTypes Building::getBuildingType() const
{
	return *buildingType;
}

std::uint_least8_t Building::getBuildingNumber() const
{
	return *buildingNumber;
}

std::uint_least8_t Building::getPosition() const
{
	return *position;
}

BuildingDeck::BuildingDeck() :
	MAX_DECK_SIZE{ new std::uint_least16_t(144) },
	deckSize{ new std::uint_least16_t(144) },
	deckContent{NULL}
{
	deckContent->reserve(144);

	ResourceTypes buildingType;

	for (std::uint_fast16_t i = 0; i < 4; i++)
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
		case 6:
			buildingType = ResourceTypes::WOOD;
			break;
		default:
			break;
		}

		for (std::uint_fast8_t j = 0; j < 6; j++)
		{
			for (std::uint_fast8_t k = 0; k < 6; k++)
			{
				deckContent->emplace_back(Building(buildingType, j));
			}
		}
	}
}

BuildingDeck::~BuildingDeck()
{
	delete MAX_DECK_SIZE;
	delete deckSize;
	delete[] deckContent;
}

std::uint_least16_t BuildingDeck::getDeckSize() const
{
	return *deckSize;
}
/*
Building* BuildingDeck::draw() const
{
	if (*deckSize > 0)
	{
		(*deckSize)--;
		return &deckContent->at(*deckSize);
	}
	else
	{
		return nullptr;
	}
}*/
