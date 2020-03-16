#include "./Part-3_5.h"
#include "./Player.h"
#include <iostream>

void DrawBuilding(Player& player)
{
	std::uint_fast8_t buildingCountToDraw{ 4 };

	for (std::pair<ResourceTypes, std::uint_fast16_t> const& element: *player.resourceTracker().score)
	{
		if (element.second != 0)
			buildingCountToDraw--;
	}
}