#include "tile.h"
#include "bag.h"
#include <iostream>

using namespace std;

void testTile();
void testBag();

int main()
{
	testBag();
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
