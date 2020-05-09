#include "tile.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "play.h"

using namespace std;

/*
 * The Play class tracks all aspects of the placement of tiles by a player such as points earned,
 * words made, duration of play, tiles placed, etc
 */
Play::Play(Player* p)
{
	pointsEarned = 0;
	playMaker = p;
}

Play::~Play()
{
	delete playMaker;
}

void Play::setPlayer(Player* p)
{
	playMaker = p;
}

bool Play::validate(string tileStr, Board* b, int r, int c, char dir)
{
	int max = tileStr.length();
	bool result = false;
	Square* curr;

	if(dir == 'h') {
		int currCol = c;
		for(int i = 0; i < max; i++) {
			curr = b->getSquare(r, currCol);
			if(curr) {
				Square* currLeft = curr->getLeft();
				Square* currRight = curr->getRight();
				Square* currAbove = curr->getAbove();
				Square* currBelow = curr->getBelow();

				result =
				    ( currLeft && !currLeft->isEmpty() ) ||
				    ( currRight && !currRight->isEmpty() ) ||
				    ( currAbove && !currAbove->isEmpty() ) ||
				    ( currBelow && !currBelow->isEmpty() );

				if(result) {
					break;
				}
				else {
					currCol++;
				}
			}
			else {
				throw(string("Invalid square co-ordinates\n"));
			}
		}
	}
	else if(dir == 'v') {
		int currRow = r;
		for(int i = 0; i < max; i++) {
			curr = b->getSquare(currRow, c);
			if(curr) {
				Square* currLeft = curr->getLeft();
				Square* currRight = curr->getRight();
				Square* currAbove = curr->getAbove();
				Square* currBelow = curr->getBelow();

				result =
				    ( currLeft && !currLeft->isEmpty() ) ||
				    ( currRight && !currRight->isEmpty() ) ||
				    ( currAbove && !currAbove->isEmpty() ) ||
				    ( currBelow && !currBelow->isEmpty() );

				if(result) {
					break;
				}
				else {
					currRow++;
				}
			}
			else {
				throw(string("Invalid square co-ordinates"));
			}
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return result;
}

// vector<vector<Tile*>> getWords(string tileStr, Board* b, int r, int c, char dir)
// {
//     vector<vector<Tile*>> words;
//     vector<Tile*> currWord;
//
// }

vector<Tile*> Play::getConnectedTiles(Tile* t, char dir)
{
	Square* currSquare;
	// Tile* currTile;
	vector<Tile*> connectedTiles;

	if(dir == 'h') {
		// Search left hand side
		currSquare = t->getSquare()->getLeft();
		while(!currSquare->isEmpty()) {
			connectedTiles.push_back(currSquare->getTile());
			currSquare = currSquare->getLeft();
		}

		// Search right hand side
		currSquare = t->getSquare()->getRight();
		while(!currSquare->isEmpty()) {
			connectedTiles.push_back(currSquare->getTile());
			currSquare = currSquare->getRight();
		}
	}
	else if(dir == 'v') {
		// Search above
		currSquare = t->getSquare()->getAbove();
		while(!currSquare->isEmpty()) {
			connectedTiles.push_back(currSquare->getTile());
			currSquare = currSquare->getAbove();
		}

		// Search below
		currSquare = t->getSquare()->getBelow();
		while(!currSquare->isEmpty()) {
			connectedTiles.push_back(currSquare->getTile());
			currSquare = currSquare->getBelow();
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return connectedTiles;
}
