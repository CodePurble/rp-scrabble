#ifndef BAG_H
#define BAG_H
#include "tile.h"
#include <vector>

class Bag {
	private:
		int tileCount = 100;
		std::vector<Tile*> tiles;


	public:
		Bag();
		~Bag();

		void show();
		void shuffle();

};

#endif
