#include "Resources.h"
#include <cstdlib>
#include <time.h>

std::ostream& operator<<(std::ostream& output, const resourceTypes resource)
{
	switch (resource)
	{
	case resourceTypes::SHEEP:
		output << "Sheep";
		return output;
	case resourceTypes::STONE:
		output << "Stone";
		return output;
	case resourceTypes::WHEAT:
		output << "Wheat";
		return output;
	case resourceTypes::WOOD:
		output << "Wood";
		return output;
	default:
		output << "Resource Type Error";
		return output;
	}
}

HarvestTile::HarvestTile()
{
	this->generateResources();
}

HarvestTile::~HarvestTile()
{
	delete[] this->tileContent;
	delete[] this->position;
}

void HarvestTile::generateResources()
{
	std::uint_least8_t sheepCount{ 0 }, stoneCount{ 0 }, wheatCount{ 0 }, woodCount{ 0 };
	std::srand(time(NULL));

	for (std::uint_least8_t i = 0; i < 4; i++)
	{
		switch (std::rand() % 4 + 1)
		{
		case 1:
			sheepCount++;

			if (sheepCount <= 3)
			{
				*(this->tileContent + i) = resourceTypes::SHEEP;
			}
			else
			{
				i--;
			}

			break;
		case 2:
			stoneCount++;

			if (stoneCount <= 3)
			{
				*(this->tileContent + i) = resourceTypes::STONE;
			}
			else
			{
				i--;
			}

			break;
		case 3:
			wheatCount++;

			if (wheatCount <= 3)
			{
				*(this->tileContent + i) = resourceTypes::WHEAT;
			}
			else
			{
				i--;
			}

			break;
		case 4:
			woodCount++;

			if (woodCount <= 3)
			{
				*(this->tileContent + i) = resourceTypes::WOOD;
			}
			else
			{
				i--;
			}

			break;
		}
	}
}

void HarvestTile::rotateTileClockwise()
{
	resourceTypes _temp{ this->tileContent[3] };
	
	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		this->tileContent[3-i] = this->tileContent[2-i];
	}
	
	this->tileContent[0] = _temp;
}

void HarvestTile::rotateTileCounterClockwise()
{
	resourceTypes _temp{ this->tileContent[0] };

	for (std::uint_fast8_t i = 0; i < 3; i++)
	{
		this->tileContent[i] = this->tileContent[i+1];
	}

	this->tileContent[3] = _temp;
}

resourceTypes* HarvestTile::getTileContent()
{
	resourceTypes* content{ new resourceTypes[4] };

	for (std::int_fast8_t i = 0; i < 4; i++)
	{
		*(content + i) = *(this->tileContent + i);
	}

	return content;
}

std::uint_least8_t* HarvestTile::getPosition()
{
	std::uint_least8_t* position{ new std::uint_least8_t[2] };

	for (std::uint_fast8_t i = 0; i < 2; i++)
	{
		*(position + i) = *(this->position + i);
	}

	return position;
}

HarvestDeck::HarvestDeck()
{
}

HarvestDeck::~HarvestDeck()
{
	delete this->MAX_DECK_SIZE;
	delete this->deckSize;
	delete[] this->deckContent;
}

std::uint_least8_t HarvestDeck::getDeckSize()
{
	return *this->deckSize;
}

HarvestTile* HarvestDeck::draw()
{
	if (this->deckSize > 0)
	{
		(*this->deckSize)--;
		return &this->deckContent[*this->deckSize];
	}
	else
	{
		return nullptr;
	}
}
