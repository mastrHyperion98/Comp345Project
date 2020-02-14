#pragma once
#include<ostream>
#include <cstdint>

enum struct ResourceTypes:std::uint_least8_t { SHEEP, STONE, WHEAT, WOOD };

std::ostream& operator<<(std::ostream& output, const ResourceTypes resource);

struct HarvestTile
{
private:
	ResourceTypes* const tileContent{ new ResourceTypes[4] };
	std::uint_least8_t* const position{ new std::uint_least8_t[2] };

	void generateResources();
public:
	HarvestTile();
	~HarvestTile();

	ResourceTypes* getTileContent();
	std::uint_least8_t* getPosition();
	void rotateTileClockwise();
	void rotateTileCounterClockwise();
};

struct HarvestDeck
{
private:
	const std::uint_least8_t* const MAX_DECK_SIZE{ new std::uint_least8_t(60) };
	std::uint_least8_t* const deckSize{new std::uint_least8_t(*MAX_DECK_SIZE)};
	HarvestTile* const deckContent { new HarvestTile[*MAX_DECK_SIZE] };
	
public:
	HarvestDeck();
	~HarvestDeck();

	std::uint_least8_t getDeckSize();
	HarvestTile* draw();
};
/*
struct BuildingDeck
{
private:
	
	
public:
	BuildingDeck();

	void draw();
};
*/
/*
struct Building
{
private:


public:
	Building();

};

struct Hand
{
private:


public:
	Hand();
	void exchange();
};
*/