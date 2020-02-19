#pragma once
#include<ostream>
#include <cstdint>

enum struct ResourceTypes:std::uint_least8_t { SHEEP, STONE, WHEAT, WOOD };

std::ostream& operator<<(std::ostream& output, const ResourceTypes resource);

struct HarvestTile
{
private:
	ResourceTypes* tileContent;
	std::uint_least8_t* position;

	void generateResources();
public:
	HarvestTile();
	~HarvestTile();

	ResourceTypes* getTileContent() const;
	std::uint_least8_t* getPosition() const;
	void rotateTileClockwise();
	void rotateTileCounterClockwise();
};

struct HarvestDeck
{
private:
	const std::uint_least8_t* MAX_DECK_SIZE;
	std::uint_least8_t* deckSize;
	HarvestTile* deckContent;
	
public:
	HarvestDeck(std::uint_least8_t deckSize = 60);
	~HarvestDeck();

	std::uint_least8_t getDeckSize() const;
	HarvestTile* draw() const;
};
/*
struct BuildingDeck
{
private:
	const std::uint_least8_t* const MAX_DECK_SIZE{ new std::uint_least8_t(144) };
	std::uint_least8_t* const deckSize{ new std::uint_least8_t(*MAX_DECK_SIZE) };
	Building* const deckContent{ new Building[*MAX_DECK_SIZE] };
	
public:
	BuildingDeck();
	~BuildingDeck();

	std::uint_least8_t getDeckSize();
	Building* draw();
};

struct Building
{
private:
	const ResourceTypes* const buildingType{ new ResourceTypes() };
	//const std::uint_least8_t* const buildingNumber;
	std::uint_least8_t* const position{ new std::uint_least8_t[2] };

public:
	Building();

};*/
/*
struct Hand
{
private:


public:
	Hand();
	void exchange();
};
*/