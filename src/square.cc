#include <iostream>
#include "square.h"
#include "tile.h"

using namespace std;

Square::Square(enum_sqType st, int r, int c)
{
	sqType = st;
	tileInSquare = nullptr;
	left = right = above = below = nullptr;
	row = r;
	col = c;
}

void Square::show()
{
	cout << sqType << " @ (" << row << "," << col << ")";
}

Square* Square::getLeft()
{
	return left;
}

Square* Square::getRight()
{
	return right;
}

Square* Square::getAbove()
{
	return above;
}

Square* Square::getBelow()
{
	return below;
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
	if(tileInSquare) {
		return false;
	}
	else {
		return true;
	}
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

void Square::setAbove(Square* u)
{
	above = u;
}

void Square::setBelow(Square* d)
{
	below = d;
}

bool Square::checkNeighboursH()
{
	if(left || above || below) {
		return true;
	}
	else {
		return false;
	}
}

bool Square::checkNeighboursV()
{
	if(left || above || right) {
		return true;
	}
	else {
		return false;
	}
}
