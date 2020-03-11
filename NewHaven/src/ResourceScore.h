#pragma once
#include <iostream>
#include "../src/Resources.h"
#include "../src/GBMap.h"

struct ResourceScore
{
private:
	void adjacentTile(const Square&, const Square&, std::uint_fast8_t, std::uint_fast8_t);
	std::uint_fast8_t browseTile(const Square&, const ResourceTypes* const, const std::uint_fast8_t&);

public:
	ResourceScore();
    ResourceScore(const ResourceScore& scores);
    ResourceScore& operator=(const ResourceScore& scores);
	~ResourceScore();

    std::map<ResourceTypes, std::uint_least16_t>* score;	//Map to store the score for each resource type

	void computeScore(ResourceTrails);
	void printScore();
	bool consumeResources(ResourceTypes, std::uint_least16_t);
	bool hasResources(ResourceTypes, std::uint_least16_t);
};