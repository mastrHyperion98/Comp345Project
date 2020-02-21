#pragma once
#include <ostream>
#include <cstdint>
#include <vector>

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
	std::uint_least8_t getPosition() const;
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
	HarvestDeck(std::uint_least8_t = 60);
	~HarvestDeck();

	std::uint_least8_t getDeckSize() const;
	HarvestTile* draw() const;
};

struct Building
{
private:
	const ResourceTypes* buildingType;
	const std::uint_least8_t* buildingNumber;
	std::uint_least8_t* position;

public:
	Building(ResourceTypes = ResourceTypes::SHEEP, std::uint_least8_t = 1, std::uint_least8_t = 0);
	~Building();

	ResourceTypes getBuildingType() const;
	std::uint_least8_t getBuildingNumber() const;
	std::uint_least8_t getPosition() const;
};

struct BuildingDeck
{
private:
	const std::uint_least16_t* MAX_DECK_SIZE;
	std::uint_least16_t* deckSize;
	std::vector<Building>* deckContent;
	
public:
	BuildingDeck();
	~BuildingDeck();

	std::uint_least16_t getDeckSize() const;
	//Building* draw() const;
};
/*
struct Hand
{
private:


public:
	Hand();
	void exchange();
};
*/