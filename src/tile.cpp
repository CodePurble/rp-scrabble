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
