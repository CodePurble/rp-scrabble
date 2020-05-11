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
	pointsMade = 0;
	playMaker = p;
	playStr = "";
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
					( currLeft && !currLeft->isEmpty() )
					|| ( currRight && !currRight->isEmpty() )
					|| ( currAbove && !currAbove->isEmpty() )
					|| ( currBelow && !currBelow->isEmpty() );

				if(result) {
					playStr = tileStr;
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
					( currLeft && !currLeft->isEmpty() )
					|| ( currRight && !currRight->isEmpty() )
					|| ( currAbove && !currAbove->isEmpty() )
					|| ( currBelow && !currBelow->isEmpty() );

				if(result) {
					playStr = tileStr;
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

vector<vector<Tile*>> Play::getWords(vector<Tile*> tilesInStr, Board* b, int r, int c, char dir)
{
	vector<vector<Tile*>> words;
	vector<Tile*> placedTiles;
	int currRow = r;
	int currCol = c;
	Square* currSquare;

	try {
		if(dir == 'h') {
			currSquare = b->getSquare(currRow, currCol);
			while(!currSquare->getLeft()->isEmpty()) {
				currSquare = currSquare->getLeft();
			}

			while(!currSquare->isEmpty()) {
				placedTiles.push_back(currSquare->getTile());
				currSquare = currSquare->getRight();
			}
			words.push_back(placedTiles);

			for(Tile* t : tilesInStr) {
				currSquare = t->getSquare();
				if(!currSquare->getAbove()->isEmpty() || !currSquare->getBelow()->isEmpty()) {
					words.push_back(getConnectedWord(t, 'v'));
				}
			}
		}
		else if(dir == 'v') {
			currSquare = b->getSquare(currRow, currCol);
			while(!currSquare->getAbove()->isEmpty()) {
				currSquare = currSquare->getAbove();
			}

			while(!currSquare->isEmpty()) {
				placedTiles.push_back(currSquare->getTile());
				currSquare = currSquare->getBelow();
			}
			words.push_back(placedTiles);

			for(Tile* t : tilesInStr) {
				currSquare = t->getSquare();
				if(!currSquare->getLeft()->isEmpty() || !currSquare->getRight()->isEmpty()) {
					words.push_back(getConnectedWord(t, 'h'));
				}
			}
		}

	}
	catch(string err) {
		throw;
	}

	return words;
}

vector<Tile*> Play::getConnectedWord(Tile* t, char dir)
{
	Square* currSquare;
	vector<Tile*> connectedWord;

	if(dir == 'h') {
		currSquare = t->getSquare();
		while(!currSquare->getLeft()->isEmpty()) {
			currSquare = currSquare->getLeft();
		}

		while(!currSquare->isEmpty()) {
			connectedWord.push_back(currSquare->getTile());
			currSquare = currSquare->getRight();
		}
	}
	else if(dir == 'v') {
		currSquare = t->getSquare();
		while(!currSquare->getAbove()->isEmpty()) {
			currSquare = currSquare->getAbove();
		}

		while(!currSquare->isEmpty()) {
			connectedWord.push_back(currSquare->getTile());
			currSquare = currSquare->getBelow();
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return connectedWord;
}

void Play::calculatePoints(vector<vector<Tile*>> words)
{
	int multiplier = 1;

/*
 * enum enum_sqType {N, DWS, TWS, DLS, TLS};
 */
	for(vector<Tile*> word : words) {
		for(Tile* t : word) {
			DEBUG("pointsMade", pointsMade);
			DEBUG("sqType", t->getSquare()->getType());
			DEBUG("getPoints", t->getPoints());
			switch(t->getSquare()->getType()) {
				case N:
					pointsMade += t->getPoints();
					break;
				case DLS:
					pointsMade += 2*(t->getPoints());
					break;
				case TLS:
					pointsMade += 2*(t->getPoints());
					break;
				case TWS:
					multiplier *= 3;
					break;
				case DWS:
					multiplier *= 2;
					break;
			}
		}
	}

	pointsMade *= multiplier;
	DEBUG("Updated pointsMade", pointsMade);
}

int Play::getPointsMade()
{
	return pointsMade;
}
