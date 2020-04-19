#include <iostream>
#include "tile.h"
#include "bag.h"
#include "rack.h"

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

void Tile::show()
{
	std::cout << letter << "-" << points << std::endl;
}

void Tile::setBag(Bag* b)
{
	myBag = b;
	presentLoc = BAG;
}

void Tile::setRack(Rack* r)
{
	myRack = r;
	presentLoc = RACK;
}
