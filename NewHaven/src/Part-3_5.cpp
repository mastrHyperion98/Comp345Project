#include "./Part-3_5.h"
#include "./Player.h"
#include <iostream>

BuildingDeck bd;

void DrawBuilding(Player& player)
{
	std::uint_fast8_t buildingCountToDraw{ 4 };

	for (std::pair<ResourceTypes, std::uint_fast16_t> const& element: *player.resourceTracker().score)
	{
		if (element.second != 0)
			buildingCountToDraw--;
	}
		
	bool loopPool{ true };
	char input{ 'y' };
	std::uint_fast8_t buildingIndex;

	for (std::uint_fast8_t i = 0; i < buildingCountToDraw; i++)
	{
		if (loopPool)
		{
			std::cout << "\nEnter building card index to draw from the pool: ";

			try
			{
				std::cin >> buildingIndex;
				std::cout << '\n';

				if (buildingIndex < 0 || buildingIndex > bd.getBuildingPoolSize())
					throw std::exception();
				
				loopPool = false;
				player.drawBuildingPool(bd.buildingPoolDraw(buildingIndex));
				continue;
			}
			catch (const std::exception & e)
			{
				std::cout << "\nThe input was invalid, please enter a valid index.\n";
				i--;
				continue;
			}
		}

		std::cout << "\nDo you want to pick another card from the pool? (y/n): ";
		try
		{
			std::cin >> input;
			std::cout << '\n';

			if (input == 'y' || input == 'Y')
			{
				loopPool = true;
				continue;
			}
			else if (input == 'n' || input == 'N')
			{
				loopPool = false;
			}
			else
			{
				throw std::exception();
			}
		}
		catch (const std::exception& e)
		{
			std::cout << "\nInvalid input, try again.\n";
			i--;
			continue;
		}

		player.drawBuilding(bd.draw());
	}

	bd.fillBuildingPool();
}