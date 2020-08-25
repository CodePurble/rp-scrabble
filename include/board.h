/**
  * @file
  */
#ifndef BOARD_H
#define BOARD_H
#include "square.h"
#include "utils.h"
#include <array>
#include <vector>

class Tile;
class Player;
class Rack;

/**
 * Implements the Scrabble board
 *
 * The board is a 2D matrix of pointers to Square objects
 */
class Board {
private:
	Square* board[NUM_ROWS][NUM_COLS];
	std::array<std::string, 5> sqStrings;

public:
	Board();
	~Board();

	Square* getSquare(int r, int c);

	void show();
	bool placeTile(Tile* t, int r, int c);
	void placeTileStr(Rack* rack, std::vector<Tile*> tilesInStr, int r, int c, char dir);
	Tile* retrieve(int r, int c);
};

#endif
