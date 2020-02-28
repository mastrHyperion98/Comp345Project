#include "ResourceScore.h"

ResourceScore::ResourceScore(): score{ new std::map<ResourceTypes, std::uint_least8_t>({{ResourceTypes::SHEEP, 0}, {ResourceTypes::STONE, 0},{ResourceTypes::WHEAT, 0},{ResourceTypes::WOOD, 0}}) }
{}

ResourceScore::~ResourceScore()
{
	delete score;
}

void ResourceScore::computeScore(ResourceTrails)
{

}
