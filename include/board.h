#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "utils.h"
#include <array>

class Tile;

class Board {
	private:
		Square* board[NUM_ROWS][NUM_COLS];
		std::array<std::string, 5> sqStrings;

	public:
		Board();
		~Board();
		void show();
		bool placeTile(Tile* t, int r, int c);
};

#endif
