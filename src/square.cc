#include "square.h"
#include "tile.h"
#include <iostream>

using namespace std;

Square::Square(enum_sqType st, int r, int c)
{
	sqType = st;
	tileInSquare = nullptr;
	left = right = up = down = nullptr;
	row = r;
	col = c;
}

void Square::show()
{
	cout << sqType << " @ (" << row << "," << col << ")" << "\n";
}

Square* Square::getLeft()
{
	return left;
}

Square* Square::getRight()
{
	return right;
}

Square* Square::getUp()
{
	return up;
}

Square* Square::getDown()
{
	return down;
}

int Square::getRow()
{
	return row;
}

int Square::getCol()
{
	return col;
}

int Square::getType()
{
	return sqType;
}

bool Square::isEmpty()
{
	if(tileInSquare)
		return false;
	else
		return true;
}

void Square::setTile(Tile* t)
{
	tileInSquare = t;
}

Tile* Square::getTile()
{
	return tileInSquare;
}

void Square::setLeft(Square* l)
{
	left = l;
}

void Square::setRight(Square* r)
{
	right = r;
}

void Square::setUp(Square* u)
{
	up = u;
}

void Square::setDown(Square* d)
{
	down = d;
}
