#ifndef TILE_H
#define TILE_H

enum enum_location {BAG , RACK, BOARD};

class Tile {
	private:
		// square*, bag*, rack*
		char letter;
		int points;
		enum_location presentLoc;

	public:
		Tile(char l, int p, enum_location p_loc);
		Tile(Tile& source);
		~Tile(){}

		char getLetter();
		int getPoints();
		int getLoc();
		void setLoc(int loc);
		void show();

};

#endif
