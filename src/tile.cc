#include "tile.h"

tile::tile(char l, int p, locations p_loc)
{
	letter = l;
	points = p;
	presentLoc = p_loc;
}

tile::tile(tile& source)
{
	letter = source.letter;
	points = source.points;
	presentLoc = source.presentLoc;
}

char tile::getLetter()
{
	return letter;
}

int getPoints()
{
	return points;
}

int getLoc()
{
	switch(presentLoc){
		case bag:
			return 0;
		break;
		case rack:
			return 1;
		break;
		case board:
			return 2;
		break;
	}
}
