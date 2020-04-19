#include <iostream>
#include "rack.h"
#include "tile.h"
#include "bag.h"
#include "square.h"
#include "board.h"

using namespace std;

void testTile();
void testBag();
void testRack();
void testSquare();
void testBoard();

int main()
{
	testBoard();
	return 0;
}

void testTile()
{
	enum_location l1 = BAG;
	Tile t('a', 1, l1);
	t.show();
}

void testBag()
{
	Bag b;
	b.show();
	vector<Tile*> t = b.draw(200);
	std::cout << std::endl;
	b.show();
}

void testRack()
{
	Bag b;
	Rack r;
	b.show();
	r.show();
	r.fill(b.draw(4));
	b.show();
	r.show();
	r.fill(b.draw(1));
	b.show();
	r.show();
}

void testSquare()
{
	enum_sqType type = DWS;
	Square s(type, 4, 5);
	s.show();
}

void testBoard()
{
	Board b;
	b.show();
}
