#include "Part-3_6.h"

HarvestDeck hd;

void EndOfTurn(Player& player)
{
	/*
	The instructions demand that the resource markers be set back to 0 here.
	So far there's no way to do that and it's irrelevant.
	*/

	if (true)								//TODO: This needs to check if the player player the shipment or a regular tile
		player.drawHarvestTile(hd.draw());	//If they playe a regular card, they draw, otherwise they don't
}