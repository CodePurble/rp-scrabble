#include <iostream>
#include "rack.h"
#include "tile.h"
#include "bag.h"
#include "square.h"
#include "board.h"
#include "game.h"
#include "play.h"
#include "player.h"
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

	for(int i = 0; i < 3; i++) {
		t.push_back(new Tile('A', 1, l1));
	}

	Rack r;
	r.fill(t);
	r.show();
	try {
		cout << boolalpha;
		cout << r.isEmpty();
		// t.clear();
		// t = r.getTileStrVec("ABA");
		// r.show();
		// for(Tile* x : t)
		//     cout << x->getLetterStr();
	}
	catch(string e) {
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
	vector<Tile*> t;
	Rack r;

	for(int i = 0; i < 3; i++) {
		t.push_back(new Tile('A', 1, RACK));
	}
	b.placeTile(t.back(), 7, 7);
	b.show();
	r.show();
	Tile* temp = b.retrieve(7, 7);
	r.addTile(temp);
	b.show();
	temp->show();
	r.show();

}

void testGame()
{
	Game g;
	g.run();
}

void testPlay()
{
}
