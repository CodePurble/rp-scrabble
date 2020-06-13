/**
 * @file
 */
#ifndef DEBUG

#include "game.h"

int main()
{
	Game newGame;
	newGame.run();

	return 0;
}

#else

#include <iostream>
#include "game.h"
#include "board.h"
#include "utils.h"

void testGame();
void testBoard();

int main()
{
	testGame();
	return 0;
}

void testGame()
{
	Game g;
	g.run();
}

void testBoard()
{
	Board b;
	b.show();
}

#endif
