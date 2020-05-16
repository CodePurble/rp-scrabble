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
	int pointsMade;
	Player* playMaker;
	std::string playStr;
	std::vector<std::vector<Tile*>> wordsInPlay;

public:
	Play(Player* p);
	~Play();

	void setPlayer(Player* p);
	bool validate(std::string tileStr, Board* b, int r, int c, char dir);
	std::vector<std::vector<Tile*>> getWords(std::vector<Tile*> tilesInStr, Board* b, int r, int c, char dir);
	std::vector<Tile*> getConnectedWord(Tile* t, char dir);
	void calculatePoints(std::vector<std::vector<Tile*>> words, std::vector<Tile*> tileStrVec);
	int getPointsMade();
	bool confirmPlay();
	void reset();
	void show();
};

#endif
