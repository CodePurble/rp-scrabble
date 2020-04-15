#include "tile.h"
#include <iostream>

void testTile();

int main()
{
	testTile();
	return 0;
}

void testTile()
{
	locations l1 = BAG;
	tile t('a', 1, l1);
	t.show();

	std::cout << t.getLetter() << std::endl;
	std::cout << t.getPoints() << std::endl;
	std::cout << t.getLoc() << std::endl;

	t.setLoc(2);
	std::cout << t.getLoc() << std::endl;
}
