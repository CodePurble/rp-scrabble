#ifndef TILE_H
#define TILE_H

enum locations {0 /* bag */, 1 /* rack */, 2 /* board */};

class tile {
	private:
		char letter;
		int points;
		locations presentLoc
	public:
		tile(char l, int p, locations p_loc);
		tile(tile& source);
		~tile();

		char getLetter();
		int getPoints();
		int getLoc();
}

#endif
