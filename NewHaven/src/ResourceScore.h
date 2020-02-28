#pragma once
#include <map>
#include "../src/Resources.h"
#include "../src/GBMap.h"

struct ResourceScore
{
private:
	std::map<ResourceTypes, std::uint_least8_t>* score;



public:
	ResourceScore();
	~ResourceScore();

	void computeScore(ResourceTrails);
};