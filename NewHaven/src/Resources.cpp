#include "Resources.h"
#include <cstdlib>

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

HarvestTile* HarvestDeck::draw()
{
	if (this->deckSize > 0)
	{
		(*this->deckSize)--;
		return new HarvestTile();
	}
	else
	{
		return nullptr;
	}
}
/*
void HarvestDeck::generateHarvestTiles()
{
	constexpr HarvestTile deckContent[60];
	this->deckContent{ &deckContent };

	for (std::uint_least8_t i = 0; i < 60; i++)
	{
		deckContent[i]{ new HarvestTile() };
	}
}
*/