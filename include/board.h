#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "utils.h"
#include <array>
#include <vector>

class Tile;
class Player;

class Board {
	private:
		Square* board[NUM_ROWS][NUM_COLS];
		std::array<std::string, 5> sqStrings;

	public:
		Board();
		~Board();
		void show();
		bool placeTile(Tile* t, int r, int c);
		bool placeTileStr(std::vector<Tile*> tilesInStr, int r, int c, char dir);
};

#endif
