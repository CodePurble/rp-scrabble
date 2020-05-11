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

				result = ( currLeft && !currLeft->isEmpty() )
				||( currRight && !currRight->isEmpty() )
				||( currAbove && !currAbove->isEmpty() )
				||( currBelow && !currBelow->isEmpty() );

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

				result = ( currLeft && !currLeft->isEmpty() )
				||( currRight && !currRight->isEmpty() )
				||( currAbove && !currAbove->isEmpty() )
				||( currBelow && !currBelow->isEmpty() );

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

/*
 * vector<Tile*> Play::getConnectedTiles(Tile* t, char dir)
 * {
 *     Square* currSquare;
 *     // Tile* currTile;
 *     vector<Tile*> connectedTiles;
 *
 *     if(dir == 'h') {
 *         // Search left hand side
 *         currSquare = t->getSquare()->getLeft();
 *         while(!currSquare->isEmpty()) {
 *             connectedTiles.push_back(currSquare->getTile());
 *             currSquare = currSquare->getLeft();
 *         }
 *
 *         // Search right hand side
 *         currSquare = t->getSquare()->getRight();
 *         while(!currSquare->isEmpty()) {
 *             connectedTiles.push_back(currSquare->getTile());
 *             currSquare = currSquare->getRight();
 *         }
 *     }
 *     else if(dir == 'v') {
 *         // Search above
 *         currSquare = t->getSquare()->getAbove();
 *         while(!currSquare->isEmpty()) {
 *             connectedTiles.push_back(currSquare->getTile());
 *             currSquare = currSquare->getAbove();
 *         }
 *
 *         // Search below
 *         currSquare = t->getSquare()->getBelow();
 *         while(!currSquare->isEmpty()) {
 *             connectedTiles.push_back(currSquare->getTile());
 *             currSquare = currSquare->getBelow();
 *         }
 *     }
 *     else {
 *         throw(string("Invalid direction\n"));
 *     }
 *
 *     return connectedTiles;
 * }
 */

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
					// BOLD(" Vertical neighbours present\n");
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
					// BOLD(" Horizontal neighbours present\n");
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
			// BOLD_RED(" Adding to connectedWord... ");
			// currSquare->show();
			connectedWord.push_back(currSquare->getTile());
			currSquare = currSquare->getBelow();
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return connectedWord;
}
