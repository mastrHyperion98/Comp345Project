#pragma once
#include <iostream>
#include "../src/GBMap.h"
#include "../src/Resources.h"

int main()
{
	GBMap map(0);

	map.getSquare(7).setTile(new HarvestTile);
	map.getSquare(8).setTile(new HarvestTile);
	map.getSquare(9).setTile(new HarvestTile);
	map.getSquare(12).setTile(new HarvestTile);
	map.getSquare(13).setTile(new HarvestTile);
	map.getSquare(17).setTile(new HarvestTile);

	map.printIndexConfiguration();

	ResourceTrails connection{map.getConnectedGraph(7)};
	ResourceTrails::vertex_iterator v_start, v_end;
	ResourceTrails::adjacency_iterator e_start, e_end;
	int sourcePos, targetPos;
	ResourceTypes sourceContent, targetContent;
	short sheep{ 0 }, stone{ 0 }, wheat{ 0 }, wood{ 0 };

	for (tie(v_start, v_end) = vertices(connection); v_start != v_end; ++v_start) {
		sourcePos = connection[*v_start].getPosition();
		sourceContent = connection[*v_start].getTile().getTileContent;

		
		for (tie(e_start, e_end) = adjacent_vertices(*v_start, connection); e_start != e_end; ++e_start)
		{
			targetPos = connection[*e_start].getPosition();
			targetContent = connection[*e_start].getTile().getTileContent;

			if (targetPos == sourcePos - 1)		//Target is on the left
			{

			}
			else if (targetPos == sourcePos + 1)	//Target is on the right
			{

			}
			else if (targetPos == sourcePos - 5)	//Target is on top
			{

			}
			else	//Target is at bottom
			{

			}
		}
		cout << "\n";
	}
/*
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 */
}