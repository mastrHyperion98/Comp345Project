#include "ResourceScore.h"
#include <map>
ResourceScore::ResourceScore(): score{ new std::map<ResourceTypes, std::uint_least16_t> }
{}
ResourceScore::ResourceScore(const ResourceScore& scores){
    score = score = new std::map<ResourceTypes, std::uint_least16_t>(*scores.score);
}
ResourceScore& ResourceScore::operator=(const ResourceScore& scores){
    if(&scores == this)
        return *this;
    score = new std::map<ResourceTypes, std::uint_least16_t>(*scores.score);

    return *this;
}
ResourceScore::~ResourceScore()
{
	delete score;
}

void ResourceScore::computeScore(ResourceTrails tileCluster)
{
	score->clear();	//We clear the previously calculated score when we attempt to calculate a new one.

	for (unsigned short i = 0; i < 4; i++)
	{
		tileCluster[0].rootConnected[i] = true;	//The starting tile is the root, so all its resources are rooted
		tileCluster[0].visitedResource[i] = true;	//The starting tile is alos considered to have been entirely visited
	}

	for (std::uint_fast8_t i = 0; i < 4; i++)
	{
		((*score)[tileCluster[0].getTile()->getTileContent()[i]])++;	//Adding starting tile resources to the score
	}

	ResourceTrails::vertex_iterator v_start, v_end;
	ResourceTrails::vertex_iterator* v_direction{ &v_start };
	ResourceTrails::adjacency_iterator e_start, e_end;
	Square sourceSquare, targetSquare;
	std::uint_fast8_t sourcePos, targetPos;
	/*
	Here we will visit the whole graph breadth first counting rooted and visited resource.
	The second iteration does the exact same thing in the exact reverse order.
	That way we go up the tree from the bottom against the graph's direction.
	*/
	for (std::uint_least8_t i = 0; i < 2; i++)
	{
		for (tie(v_start, v_end) = vertices(tileCluster); v_start != v_end;)
		{
			sourceSquare = tileCluster[i == 0 ? *(*v_direction) : *(*v_direction) - 1];	//If it's the second iteration, we can't use v_end as the index because it's out of bound. v_end - 1 is in bound.
			sourcePos = sourceSquare.getPosition();

			for (tie(e_start, e_end) = adjacent_vertices(i == 0 ? *(*v_direction) : *(*v_direction) - 1, tileCluster); e_start != e_end; ++e_start)
			{
				targetSquare = tileCluster[*e_start];
				targetPos = targetSquare.getPosition();

				if (targetPos == sourcePos - 1)		//Target is on the left
				{
					adjacentTile(sourceSquare, targetSquare, 0, 1);
				}
				else if (targetPos == sourcePos + 1)	//Target is on the right
				{
					adjacentTile(sourceSquare, targetSquare, 2, 3);
				}
				else if (targetPos - sourcePos < 0)	//Target is on top because their difference is negative, which means the sourcePos is bigger than the target
				{
					adjacentTile(sourceSquare, targetSquare, 1, 2);
				}
				else	//Target is at bottom
				{
					adjacentTile(sourceSquare, targetSquare, 3, 0);
				}
			}

			if (i == 0)
			{
				v_direction = &++v_start;
			}
			else		//On the second iteration, we start from the end of the tree to the start
			{
				v_direction = &--v_end;
			}
		}

		v_direction = &v_end;	//After the first iteration, the direction will changed from end to start
	}
}

void ResourceScore::adjacentTile(const Square& sourceSquare, const Square& targetSquare, std::uint_fast8_t sourceIndex, std::uint_fast8_t targetIndex)
{
	/*
	We check the first relationship accross tiles.
	If either the source resource or the target resource has been visited before, then we check if they are equal.
	If they are it means there's the potential to add one or the other to the score.
	If they were both visited, there's nothing else to do there.
	*/
	ResourceTypes* sourceContent{ sourceSquare.getTile()->getTileContent() }, * targetContent{ targetSquare.getTile()->getTileContent() };
	
	for (std::uint_fast8_t i = 0; i < 2; i++)
	{
		if ((!targetSquare.visitedResource[targetIndex] || !sourceSquare.visitedResource[sourceIndex]) && (sourceContent[sourceIndex] == targetContent[targetIndex]))

			/*
			Here we check which on of the connected equal resources is connected to the root. If it was the resource from the source tile, we mark the target resource as visited and connected to the root too.
			We then browse through the target tile, check browseTile function.
			*/
			if (sourceSquare.rootConnected[sourceIndex])
			{
				targetSquare.visitedResource[targetIndex] = true;
				targetSquare.rootConnected[targetIndex] = true;

				(*score)[targetContent[targetIndex]] += browseTile(targetSquare, targetContent, targetIndex);	//The total of the adjacent resources in the adjacent tile is stored in the total score for the specific resource type.
			}
			else if (targetSquare.rootConnected[targetIndex])	//If the target tile is root and not the source tile, then we will do the same as previously, but in the other sense. The source tile will be evaluated for resources and added to the total score.
			{
				sourceSquare.rootConnected[sourceIndex] = true;
				sourceSquare.visitedResource[sourceIndex] = true;

				(*score)[sourceContent[sourceIndex]] += browseTile(sourceSquare, sourceContent, sourceIndex);
			}

		sourceIndex = ((sourceIndex - 1) + 4) % 4;
		targetIndex = (targetIndex + 1) % 4;
		/*
		The second time is exactly the same thing as the first except that we evaluate the second resource of the source tile with the second resource of the target tile.
		Remeber that adjacent tiles are connected via two resources. As mentioned above the function, the second source resource is the first one decremented and the the second target resource is the first one incremented.
		That forces us to use modulo to stay in array bounds.
		*/
	}

	delete[] sourceContent;
	delete[] targetContent;
}

/*
This function's purpose is to count equal adjacent resources to a specific index. Basically finding the connected resource within a single tile instead of accross tiles like adjecentTile().
Every resource counted here is marked as visited and rooted. The idea with this function is to check for equal resources to the one in index clockwise, then counter-clockwise.
It returns an integer that will be added to the score for the resource specific to the passed index.
*/
std::uint_fast8_t ResourceScore::browseTile(const Square& square, const ResourceTypes* const content, const std::uint_fast8_t& index)
{
	std::uint_fast8_t j{ 1 }, i{ static_cast<std::uint_fast8_t>((index + j) % 4) }, total{ 1 }; //total defaults to one because we count the resource at the index. j defaults to 1 because we want to check the index right after the current one.
	/*
	index + j % 4 is to point to the next resource in the array of resources. Its purpose is to move circularly and never go out of bound.
	We make sure that the next resource was not visited before and that it is equal to the previous.
	If it was the case, we make it visited and rooted, rooted because the starting resource is rooted too. Rooted resources make adjacent resources rooted too.
	We then increment the total and j to proceed to the next resource in the tile.
	*/
	for (std::uint_fast8_t k = 0; k < 2; k++)
	{
		while ((!square.visitedResource[i]) && (content[index] == content[i]))
		{
			square.visitedResource[i] = true;
			square.rootConnected[i] = true;

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

void ResourceScore::printScore()
{
	for (std::pair<ResourceTypes, std::uint_least16_t> i : *score)	//Printing score
	{
		std::cout << '\n' << i.first << ":\t" << i.second << '\n';
	}
}

bool ResourceScore::consumeResources(ResourceTypes type, std::uint_least16_t amount) {
    // check if the resource is contianed within
    if(hasResources(type, amount)) {
        (*score)[type] = (*score)[type] - amount;
        return true;
    }

    return false;
}

bool ResourceScore::hasResources(ResourceTypes type, std::uint_least16_t amount){
    // check if the resource is contianed within
    if(score->find(type) != score->end()){
        if ((*score)[type] >= amount){
            return true;
        }
    }
    return false;
}
