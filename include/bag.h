#ifndef BAG_H
#define BAG_H
#include <vector>

class Tile;

class Bag {
	private:
		int tileCount = 100;
		std::vector<Tile*> bag;

	public:
		Bag();
		~Bag();

		void show();
		void shuffle();
		std::vector<Tile*> draw(int count);

};

#endif
