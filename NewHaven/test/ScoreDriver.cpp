#pragma once
#include <iostream>
#include "../src/GBMap.h"
#include "../src/Resources.h"

void adjacentTile(const ResourceTypes* const, const ResourceTypes* const, std::map<ResourceTypes, unsigned short>&, const HarvestTile* const, const HarvestTile* const, unsigned short, unsigned short);

unsigned short browseTile(const HarvestTile* const, const ResourceTypes* const, const unsigned short&);

int main()
{
	GBMap map(0);

/*
 * -  00 01 02 03 04 -
 * -  05 06 07 08 09 -
 * -  10 11 12 13 14 -
 * -  15 16 17 18 19 -
 * -  21 22 23 24 25 -
 */

	map.getSquare(6)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::WOOD, ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::WOOD }*/));	//I've created a HarvestTile constructor that takea a custom content array
	map.getSquare(7)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::WHEAT }*/));
	map.getSquare(8)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::STONE }*/));
	map.getSquare(11)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::WHEAT, ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::STONE }*/));
	map.getSquare(13)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::WHEAT, ResourceTypes::WOOD, ResourceTypes::STONE }*/));	//Here we create all the tile where we want them with the content wanted
	map.getSquare(14)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT, ResourceTypes::WHEAT }*/));
	map.getSquare(16)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::WOOD, ResourceTypes::SHEEP }*/));
	map.getSquare(17)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::STONE, ResourceTypes::WOOD, ResourceTypes::SHEEP }*/));
	map.getSquare(18)->setTile(new HarvestTile(/*new ResourceTypes[4]{ ResourceTypes::STONE, ResourceTypes::WOOD, ResourceTypes::WOOD, ResourceTypes::WOOD }*/));

	/*Creating a variable for every tile to store its content for the sole purpose of printing it to console.
	* They are all pointers because tileContent is an array.
	*/

	ResourceTypes* t1{ map.getSquare(6)->getTile()->getTileContent() }, *t2{ map.getSquare(7)->getTile()->getTileContent() }, *t3{ map.getSquare(8)->getTile()->getTileContent() }, *t4{ map.getSquare(11)->getTile()->getTileContent() },
		*t5{ map.getSquare(13)->getTile()->getTileContent() }, *t6{ map.getSquare(14)->getTile()->getTileContent() }, *t7{ map.getSquare(16)->getTile()->getTileContent() }, *t8{ map.getSquare(17)->getTile()->getTileContent() }, *t9{ map.getSquare(18)->getTile()->getTileContent() };

	/*
	This printing part is where I printed the tiles for a visual support. We print line by line every row of the connected tiles seperating every string with a tab.
	When there is no tile, we create the blank space with 3 consecutive tabs.
	*/

	std::cout << '\n' << t1[0] << '\t' << t1[1] << '\t' << t2[0] << '\t' << t2[1] << '\t' << t3[0] << '\t' << t3[1] <<
		'\n' << t1[3] << '\t' << t1[2] << '\t' << t2[3] << '\t' << t2[2] << '\t' << t3[3] << '\t' << t3[2] <<
		"\n\n" << t4[0] << '\t' << t4[1] << '\t' << '\t' << '\t' << t5[0] << '\t' << t5[1] << '\t' << t6[0] << '\t' << t6[1] <<
		'\n' << t4[3] << '\t' << t4[2] << '\t' << '\t' << '\t' << t5[3] << '\t' << t5[2] << '\t' << t6[3] << '\t' << t6[2] << 
		"\n\n" << t7[0] << '\t' << t7[1] << '\t' << t8[0] << '\t' << t8[1] << '\t' << t9[0] << '\t' << t9[1] <<
		'\n' << t7[3] << '\t' << t7[2] << '\t' << t8[3] << '\t' << t8[2] << '\t' << t9[3] << '\t' << t9[2] << "\n\n";

	unsigned short startTile{ 13 };	//Root tile on the board

	/*
	Created a rootConnected attribute to the HarvestTile. I also created a visitedResource attribute. They're both an array of 4 elements like tileContent. In both cases, every element of the array represents a resource in the tileContent array.
	All resources of the starting tile are rooted. That means that we will only add to the score the resources equal and adjacent to them. Once an adjacent resource is added to the score, we make it visited as to not count it twice.
	When the resource adjacent to a root resource is counted, we also make it rooted so that resources equal and adjacent to it can also be counted. In this way all resource trails connected to the initial tile resources give each other the
	rooted property and the only resources that can be counted to the score are rooted ones.
	*/

	for (unsigned short i = 0; i < 4; i++)
	{
		map.getSquare(startTile)->getTile()->rootConnected[i] = true;	//The starting tile is the root, so all its resources are rooted
		map.getSquare(startTile)->getTile()->visitedResource[i] = true;
	}

	map.printIndexConfiguration();

	cout << '\n';

	ResourceTrails tileCluster{map.getConnectedGraph(startTile)};
	ResourceTrails::vertex_iterator v_start, v_end;
	ResourceTrails::adjacency_iterator e_start, e_end;
	HarvestTile* sourceTile, *targetTile;
	int sourcePos, targetPos;
	ResourceTypes* sourceContent, *targetContent;
	std::map<ResourceTypes, unsigned short> resourceTotal{ {ResourceTypes::SHEEP, 0}, {ResourceTypes::STONE, 0},{ResourceTypes::WHEAT, 0},{ResourceTypes::WOOD, 0} };	//Map for the final score
	
	for (unsigned short i = 0; i < 4; i++)
	{
		resourceTotal[tileCluster[0].getTile()->getTileContent()[i]]++;	//Adding starting tile resources to the score
	}

	for (tie(v_start, v_end) = vertices(tileCluster); v_start != v_end; ++v_start) {
		sourceTile = tileCluster[*v_start].getTile();
		sourcePos = tileCluster[*v_start].getPosition();
		sourceContent = tileCluster[*v_start].getTile()->getTileContent();
		cout << tileCluster[*v_start].getPosition() << " is connected with ";
		
		for (tie(e_start, e_end) = adjacent_vertices(*v_start, tileCluster); e_start != e_end; ++e_start)
		{
			targetTile = tileCluster[*e_start].getTile();
			targetPos = tileCluster[*e_start].getPosition();
			targetContent = tileCluster[*e_start].getTile()->getTileContent();

			if (targetPos == sourcePos - 1)		//Target is on the left
			{
				adjacentTile(sourceContent, targetContent, resourceTotal, sourceTile, targetTile, 0, 1);
			}
			else if (targetPos == sourcePos + 1)	//Target is on the right
			{
				adjacentTile(sourceContent, targetContent, resourceTotal, sourceTile, targetTile, 2, 3);
			}
			else if (targetPos == sourcePos - 5)	//Target is on top
			{
				adjacentTile(sourceContent, targetContent, resourceTotal, sourceTile, targetTile, 1, 2);
			}
			else	//Target is at bottom
			{
				adjacentTile(sourceContent, targetContent, resourceTotal, sourceTile, targetTile, 3, 0);
			}

			cout << tileCluster[*e_start].getPosition() << " ";
		}

		cout << '\n';
	}

	for (std::pair<ResourceTypes, unsigned short> i: resourceTotal)	//Printing score
	{
		std::cout << '\n' << i.first << ":\t" << i.second << '\n';
	}
}

/*
The parameters are messy, but I didn't care. I passed to the function everything it needed to work; basically everything declared in main.
The names are self descriptive. The source/target index is basically where the resources connect accross tiles, it's predetermined depending on the position of the tiles relative to each other.
For example when a tile at the bottom of another, they will connect from resources at index [3]<->[0] and [2]<->[1]. In this case we only use the first relationship, the second one is implied
by incrementing the source index and decrementing the target index.
*/
void adjacentTile(const ResourceTypes* const sourceContent, const ResourceTypes* const targetContent, std::map<ResourceTypes, unsigned short>& resourceTotal, const HarvestTile* const sourceTile, const HarvestTile* const targetTile, unsigned short sourceIndex, unsigned short targetIndex)
{
	/*
	We check the first relationship accross tiles.
	If either the source resource or the target resource has been visited before, then we check if they are equal.
	If they are it means there's the potential to add one or the other to the score.
	If they were both visited, there's nothing else to do there.
	*/
	for (std::uint_fast8_t i = 0; i < 2; i++)
	{
		if ((!targetTile->visitedResource[targetIndex] || !sourceTile->visitedResource[sourceIndex]) && (sourceContent[sourceIndex] == targetContent[targetIndex]))

		/*
		Here we check which on of the connected equal resources is connected to the root. If it was the resource from the source tile, we mark the target resource as visited and connected to the root too.
		We then browse through the target tile, check browseTile function.
		*/
		if (sourceTile->rootConnected[sourceIndex])
		{
			targetTile->visitedResource[targetIndex] = true;
			targetTile->rootConnected[targetIndex] = true;
		
			resourceTotal[targetContent[targetIndex]] += browseTile(targetTile, targetContent, targetIndex);	//The total of the adjacent resources in the adjacent tile is stored in the total score for the specific resource type.
		}
		else if (targetTile->rootConnected[targetIndex])	//If the target tile is root and not the source tile, then we will do the same as previously, but in the other sense. The source tile will be evaluated for resources and added to the total score.
		{
			sourceTile->rootConnected[sourceIndex] = true;
			sourceTile->visitedResource[sourceIndex] = true;

			resourceTotal[targetContent[sourceIndex]] += browseTile(sourceTile, sourceContent, sourceIndex);
		}
		
		sourceIndex = ((sourceIndex - 1) + 4) % 4;
		targetIndex = (targetIndex + 1) % 4;
	/*
	The second time is exactly the same thing as the first except that we evaluate the second resource of the source tile with the second resource of the target tile.
	Remeber that adjacent tiles are connected via two resources. As mentioned above the function, the second source resource is the first one decremented and the the second target resource is the first one incremented.
	That forces us to use modulo to stay in array bounds.
	*/
	}
}
	
/*
This function's purpose is to count equal adjacent resources to a specific index. Basically finding the connected resource within a single tile instead of accross tiles like adjecentTile().
Every resource counted here is marked as visited and rooted. The idea with this function is to check for equal resources to the one in index clockwise, then counter-clockwise.
It returns an integer that will be added to the score for the resource specific to the passed index.
*/
unsigned short browseTile(const HarvestTile* const tile, const ResourceTypes* const content, const unsigned short& index)
{
	unsigned short j{ 1 }, i{ static_cast<unsigned short>((index + j) % 4) }, total{ 1 }; //total defaults to one because we count the resource at the index. j defaults to 1 because we want to check the index right after the current one.
	/*
	index + j % 4 is to point to the next resource in the array of resources. Its purpose is to move circularly and never go out of bound.
	We make sure that the next resource was not visited before and that it is equal to the previous.
	If it was the case, we make it visited and rooted, rooted because the starting resource is rooted too. Rooted resources make adjacent resources rooted too.
	We then increment the total and j to proceed to the next resource in the tile.
	*/
	for (std::uint_fast8_t k = 0; k < 2; k++)
	{
		while ((!tile->visitedResource[i]) && (content[index] == content[i]))
		{
			tile->visitedResource[i] = true;
			tile->rootConnected[i] = true;

			total++;
			j++;
			i = (index + j) % 4;
		}
		/*
		We're redoing the first part counter-clockwise this time, so we reset j.
		Here index - j + 4 % 4 has the same purpose as the one above except that the +4 will not allow index - j to be negative. C++ can not apply modulus to negative numbers.
		*/
		j = 1, i = ((index - j) + 4) % 4;
	}

	return total;
}
