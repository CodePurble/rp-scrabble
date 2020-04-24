#include <iostream>
#include "rack.h"
#include "tile.h"
#include "bag.h"
#include "square.h"
#include "board.h"
#include "game.h"

using namespace std;

void testTile();
void testBag();
void testRack();
void testSquare();
void testBoard();
void testGame();

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
	cout << "\n";
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
	enum_sqType type = N;
	Square s(type, 4, 5);
	s.show();
}

void testBoard()
{
	Bag bag;
	Board b;
	b.show();
	cout << "\n\n\n\n\n\n";
	b.placeTile(bag.draw(1).back(), 7, 7);
	b.show();
}

void testGame()
{
	Game g;
	g.run();
}
