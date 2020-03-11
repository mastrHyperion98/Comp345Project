#pragma once
#include <ostream>
#include <cstdint>
#include <vector>

enum struct ResourceTypes:std::uint_least8_t { SHEEP, STONE, WHEAT, WOOD };	//These are the resources for the tiles

std::ostream& operator<<(std::ostream& output, const ResourceTypes& resource); //Define what printing the resource enum do

struct HarvestTile
{
private:
	ResourceTypes* tileContent;	//Array of resource types

public:

	HarvestTile(ResourceTypes*);
    HarvestTile(const HarvestTile &tile);
	~HarvestTile();

	HarvestTile& operator=(const HarvestTile&);

	ResourceTypes* getTileContent() const;	//Returns a copy of the tileContent array

	void rotateTileClockwise();
	void rotateTileCounterClockwise();	//For tile rotation
};

struct HarvestDeck
{
private:
	const std::uint_least8_t* const MAX_DECK_SIZE{ new std::uint_least8_t(60) };
	std::uint_least8_t* deckSize;
	std::vector<HarvestTile*>* deckContent; //Array of harvest tile objects
	
public:
	HarvestDeck();
	~HarvestDeck();

	std::uint_least8_t getDeckSize() const;

	HarvestTile* draw() const;	//Return a pointer to a harvest tile in deckContent
};

struct Building
{
private:
	ResourceTypes* buildingType;	//Determines resource
	std::uint_least8_t* buildingNumber;
	bool* faceUp;	//Either the card is flipped or not

public:
	Building(ResourceTypes = ResourceTypes::SHEEP, std::uint_least8_t = 1);
	Building(const Building &building);
	~Building();

	Building& operator=(const Building&);

	bool isFlipped() const;		//Return the state of the card, flipped or not
	ResourceTypes getBuildingType() const;
	std::uint_least8_t getBuildingNumber() const;

	bool flipCard();
};

struct BuildingDeck
{
private:
	const std::uint_least8_t* const MAX_DECK_SIZE{ new std::uint_least8_t(144) };
	std::uint_least8_t* deckSize;
	std::vector<Building*>* deckContent;	//Vector of pointers for building cards
	
public:
	BuildingDeck();
	~BuildingDeck();

	std::uint_least8_t getDeckSize() const;

	Building* draw() const;
};

struct Hand
{
private:

public:
	Hand();
	~Hand();
	/*
	Every player is supposed to have a hand.
	It's contains a vector for tiles and building cards.
	*/
    std::vector<HarvestTile*>* harvestTiles;
    HarvestTile* shipment;
    std::vector<Building*>* buildings;
};
