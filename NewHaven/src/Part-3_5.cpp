#include "./Part-3_5.h"
#include "Setting.h"
#include "GameController.h"
#include <iostream>

BuildingDeck bd;

void DrawBuilding(Player& player)
{
	std::uint_fast8_t buildingCountToDraw{ 4 };

	for (std::pair<ResourceTypes, std::uint_fast16_t> const& element: GameController::current->game_settings->tracker->getScore())
	{
		if (element.second != 0)
			buildingCountToDraw--;
	}
		
	bool loopPool{ true };

	for (std::uint_fast8_t i = 0; i < buildingCountToDraw; i++)
	{
		std::uint_fast16_t buildingIndex;
		char input;

		if (loopPool)
		{
			std::cout << "\nEnter building card index to draw from the pool: ";

			try
			{
				std::cin >> buildingIndex;
				std::cout << '\n';
				
				if (std::cin.fail() || buildingIndex <= 0 || buildingIndex > bd.getBuildingPoolSize())
					throw std::exception();

				loopPool = false;
				player.drawBuildingPool(bd.buildingPoolDraw(buildingIndex - 1));
				continue;
			}
			catch (const std::exception&)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				loopPool = true;
				i--;
				continue;
			}
			else if (input == 'n' || input == 'N')
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				loopPool = false;
			}
			else
			{
				throw std::exception();
			}
		}
		catch (const std::exception& e)
		{

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nInvalid input, try again.\n";
			i--;
			continue;
		}

		player.drawBuilding(bd.draw());
	}

	bd.fillBuildingPool();
}