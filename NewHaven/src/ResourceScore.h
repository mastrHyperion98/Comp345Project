#pragma once
#include <iostream>
#include "../src/Resources.h"
#include "../src/GBMap.h"

struct ResourceScore
{
private:
	std::map<ResourceTypes, std::uint_least16_t>* score;

	void adjacentTile(const Square&, const Square&, std::uint_fast8_t, std::uint_fast8_t);
	std::uint_fast8_t browseTile(const Square&, const ResourceTypes* const, const std::uint_fast8_t&);

public:
	ResourceScore();
	~ResourceScore();

	void computeScore(ResourceTrails);
	void printScore();
};