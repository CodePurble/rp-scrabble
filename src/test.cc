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
	testGame();
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
	enum_location l1 = RACK;
	vector<Tile*> t;

	for(int i = 0; i < 7; i++)
		t.push_back(new Tile('A', 1, l1));

	Rack r;
	r.fill(t);
	r.show();
	try{
		t.clear();
		t = r.getTileStrVec("AAA");
		r.show();
		for(Tile* x : t)
			cout << x->getLetterStr();
	}
	catch(string e){
		BOLD_RED(e);
		cout << endl;
	}
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
