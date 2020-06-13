/**
 * @file
 */
#ifndef PLAY_H
#define PLAY_H
#include <string>
#include <vector>

/**
 * Implements a "play"
 *
 * A play is made when a player places a word on the board, adds the points receieved to their
 * score, and refills their rack.
 *
 * The Play class tracks all aspects of the placement of tiles by a player such as points earned,
 * words made, tiles placed, etc
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
