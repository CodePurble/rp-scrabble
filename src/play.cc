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

void Play::show()
{
	string wordStr = "";
	for(vector<Tile*> word : wordsInPlay) {
		for(Tile* t : word) {
			wordStr.append(t->getLetterStr());
		}
		wordStr.append(" + ");
	}
	if(!wordStr.empty()) {
		wordStr.replace(wordStr.end()-3, wordStr.end(), "");
	}

	BOLD_WHITE_FG(" Words in play: " + wordStr + "\n");
	BOLD_WHITE_FG(" " + to_string(pointsMade) + " points\n");
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
			try {
				curr = b->getSquare(r, currCol);
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
			catch(string err) {
				throw;
			}
		}
	}
	else if(dir == 'v') {
		int currRow = r;
		try {
			for(int i = 0; i < max; i++) {
				curr = b->getSquare(currRow, c);
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
		}
		catch(string err) {
			throw;
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return result;
}

vector<vector<Tile*>> Play::getWords(vector<Tile*> tilesInStr, Board* b, int r, int c, char dir)
{
	vector<Tile*> placedTiles;
	int currRow = r;
	int currCol = c;
	Square* currSquare;

	try {
		if(dir == 'h') {
			try {
				currSquare = b->getSquare(currRow, currCol);
				while(currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty()) {
					currSquare = currSquare->getLeft();
				}

				while(currSquare && !currSquare->isEmpty()) {
					placedTiles.push_back(currSquare->getTile());
					currSquare = currSquare->getRight();
				}
				wordsInPlay.push_back(placedTiles);

				for(Tile* t : tilesInStr) {
					currSquare = t->getSquare();
					if(( currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty() )
						|| ( currSquare && currSquare->getBelow() && !currSquare->getBelow()->isEmpty() )) {
						wordsInPlay.push_back(getConnectedWord(t, 'v'));
					}
				}
			}
			catch(string err) {
				throw;
			}
		}
		else if(dir == 'v') {
			try {
				currSquare = b->getSquare(currRow, currCol);
				while(currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty()) {
					if(currSquare) {
						currSquare = currSquare->getAbove();
					}
				}

				while(currSquare && !currSquare->isEmpty()) {
					placedTiles.push_back(currSquare->getTile());
					currSquare = currSquare->getBelow();
				}
				wordsInPlay.push_back(placedTiles);

				for(Tile* t : tilesInStr) {
					currSquare = t->getSquare();
					if(( currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty() )
						|| ( currSquare && currSquare->getRight() && !currSquare->getRight()->isEmpty() )) {
						wordsInPlay.push_back(getConnectedWord(t, 'h'));
					}
				}
			}
			catch(string err) {
				throw;
			}
		}

	}
	catch(string err) {
		throw;
	}

	return wordsInPlay;
}

vector<Tile*> Play::getConnectedWord(Tile* t, char dir)
{
	Square* currSquare;
	vector<Tile*> connectedWord;

	if(dir == 'h') {
		currSquare = t->getSquare();
		while(currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty()) {
			currSquare = currSquare->getLeft();
		}

		while(currSquare && !currSquare->isEmpty()) {
			connectedWord.push_back(currSquare->getTile());
			currSquare = currSquare->getRight();
		}
	}
	else if(dir == 'v') {
		currSquare = t->getSquare();
		while(currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty()) {
			currSquare = currSquare->getAbove();
		}

		while(currSquare && !currSquare->isEmpty()) {
			connectedWord.push_back(currSquare->getTile());
			currSquare = currSquare->getBelow();
		}
	}
	else {
		throw(string("Invalid direction\n"));
	}

	return connectedWord;
}

void Play::calculatePoints(vector<vector<Tile*>> words, vector<Tile*> tileStrVec)
{
	int multiplier = 1;

/*
 * enum enum_sqType {N, DWS, TWS, DLS, TLS};
 */
	for(vector<Tile*> word : words) {
		for(Tile* t : word) {
			switch(t->getSquare()->getType()) {
				case N:
					pointsMade += t->getPoints();
					break;
				case DLS:
					if(tilePresent(tileStrVec, t)) {
						pointsMade += 2*(t->getPoints());
					}
					else {
						t->show();
						pointsMade += t->getPoints();
					}
					break;
				case TLS:
					if(tilePresent(tileStrVec, t)) {
						pointsMade += 3*(t->getPoints());
					}
					else {
						pointsMade += t->getPoints();
					}
					break;
				case TWS:
					pointsMade += t->getPoints();
					if(tilePresent(tileStrVec, t)) {
						multiplier *= 3;
					}
					break;
				case DWS:
					pointsMade += t->getPoints();
					if(tilePresent(tileStrVec, t)) {
						multiplier *= 2;
					}
					break;
			}
		}
	}
	pointsMade *= multiplier;
}

int Play::getPointsMade()
{
	return pointsMade;
}

bool Play::confirmPlay()
{
	char ch;
	PALE_GREEN_FG(" Confirm the play? (y/n) ");
	cin >> ch;

	switch(ch) {
		case 'y':
			return true;
			break;
		case 'n':
			return false;
			break;
		default:
			return false;
			break;
	}
}

void Play::reset()
{
	pointsMade = 0;
	wordsInPlay.clear();
	playStr = "";
}
