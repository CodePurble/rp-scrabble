#ifndef PLAY_H
#define PLAY_H
#include <string>
#include <vector>

/*
 * A play is made when a player places a word on the board, adds the points receieved to their
 * score, and refills their rack.
 *
 * When validating a play, check whether at least one tile has got a new neighbour if yes, then play
 * is validated
 *
 * When calculating points gained, check all tile paths that have a new tile in them
 */

class Player;
class Board;
class Tile;

class Play {
	private:
		int pointsEarned;
		Player* playMaker;

	public:
		Play();
		Play(Player* p);
		~Play();

		void setPlayer(Player* p);
		bool validate(std::vector<Tile*> tilesInStr, Board* b, int r, int c, char dir);
};

#endif
