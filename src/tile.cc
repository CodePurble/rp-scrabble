#include "tile.h"
#include <iostream>

Tile::Tile(char l, int p, enum_location p_loc)
{
	letter = l;
	points = p;
	presentLoc = p_loc;
}

Tile::Tile(Tile& source)
{
	letter = source.letter;
	points = source.points;
	presentLoc = source.presentLoc;
}

char Tile::getLetter()
{
	return letter;
}

int Tile::getPoints()
{
	return points;
}

int Tile::getLoc()
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

void Tile::setLoc(int loc)
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

void Tile::show()
{
	std::cout << letter << "-" << points << std::endl;
}

