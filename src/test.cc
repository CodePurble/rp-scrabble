#include <iostream>
#include "rack.h"
#include "tile.h"
#include "bag.h"
#include "square.h"
#include "board.h"
#include "game.h"
#include "play.h"
#include "utils.h"

using namespace std;

void testTile();
void testBag();
void testRack();
void testSquare();
void testBoard();
void testGame();
void testPlay();

int main()
{
	testPlay();
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
		t = r.getTileStrVec("ABA");
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
	int r = 6, c = 7;
	b.placeTile(new Tile('a', 1, BAG), r, c);
	c++;
	b.placeTile(new Tile('b', 1, BAG), r, c);
	b.getSquare(r, c)->show();
	b.show();
}

void testGame()
{
	Game g;
	g.run();
}

void testPlay()
{
	enum_location l1 = RACK;
	vector<Tile*> t1, t2;

	for(int i = 0; i < 3; i++)
		t1.push_back(new Tile('A', 1, l1));

	for(int i = 0; i < 3; i++)
		t2.push_back(new Tile('B', 1, l1));

	Board* b = new Board();
	Play p;

	cout << boolalpha;
	b->placeTileStr(t1, 7, 7, 'h');
	b->show();

	cout << p.validate(t2, b, 4, 23, 'v');
}
