#include "tile.h"
#include <iostream>

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

int tile::getPoints()
{
	return points;
}

int tile::getLoc()
{
	switch(presentLoc){
		case BAG:
			return 0;
		break;
		case RACK:
			return 1;
		break;
		case BOARD:
			return 2;
		break;
		default:
			return -1;
	}
}

void tile::setLoc(int loc)
{
	switch(loc){
		case 0:
			presentLoc = BAG;
		break;
		case 1:
			presentLoc = RACK;
		break;
		case 2:
			presentLoc = BOARD;
		break;
	}
}

void tile::show()
{
	std::cout << letter << "-" << points << std::endl;
}

