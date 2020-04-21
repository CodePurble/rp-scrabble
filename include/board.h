#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "utils.h"

class Tile;

class Board {
	private:
		Square* board[NUM_ROWS][NUM_COLS];

	public:
		Board();
		~Board();
		void show();
		bool placeTile(Tile* t, int r, int c);
};

#endif
