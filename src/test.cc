#include "rack.h"
#include <iostream>

using namespace std;

void testTile();
void testBag();
void testRack();

int main()
{
	testRack();
	return 0;
}

void testTile()
{
	enum_location l1 = BAG;
	Tile t('a', 1, l1);
	t.show();

	std::cout << t.getLetter() << std::endl;
	std::cout << t.getPoints() << std::endl;
	std::cout << t.getLoc() << std::endl;

	t.setLoc(2);
	std::cout << t.getLoc() << std::endl;
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
