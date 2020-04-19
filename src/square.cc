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
	cout << sqType << " @ (" << row << "," << col << ")" << endl;
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
