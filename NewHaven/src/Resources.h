#pragma once
#include <cstdint>

enum struct resourceTypes:std::uint_least8_t { SHEEP, STONE, WHEAT, WOOD };

struct HarvestTile
{
private:
	resourceTypes* const tileContent{ new resourceTypes[4] };
	std::uint_least8_t* const position{ new std::uint_least8_t[2] };

	void generateResources();
public:
	HarvestTile();
	~HarvestTile();

	resourceTypes* getTileContent();
	std::uint_least8_t* getPosition();
};

struct HarvestDeck
{
private:
	const std::uint_least8_t* const MAX_DECK_SIZE{ new std::uint_least8_t(60) };
	std::uint_least8_t* const deckSize{ new std::uint_least8_t(60) };
	const HarvestTile* const deckContent{ new HarvestTile[60] };
	
	//void generateHarvestTiles();

public:
	HarvestDeck();
	~HarvestDeck();

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