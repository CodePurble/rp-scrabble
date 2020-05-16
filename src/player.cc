#include <iostream>
#include "player.h"
#include "bag.h"
#include "tile.h"
#include "rack.h"
#include "board.h"
#include "utils.h"

using namespace std;

Player::Player(string n)
{
	score = 0;
	turn = false;
	playerName = n;
	rack = new Rack();
}

Player::~Player()
{
	delete rack;
}

void Player::show()
{
	showScore();
	cout << "\n";

	rack->show();
	cout << "\n";
}

void Player::showScore()
{
	if(turn) {
		BOLD_BRIGHT_GREEN_FG(" " + playerName + ": " + to_string(score) + " points");
	}
	else {
		BOLD_WHITE_FG(" " + playerName + ": " + to_string(score) + " points");
	}
}

string Player::getName()
{
	return playerName;
}

int Player::getScore()
{
	return score;
}

void Player::setName(string name)
{
	playerName = name;
}

void Player::updateScore(int points)
{
	score += points;
}

void Player::draw(int count, Bag* b)
{
	rack->fill(b->draw(count));
}

bool Player::placeTile(Tile* t, Board* b, int r, int c)
{
	return(b->placeTile(t, r, c));
}

void Player::toggleTurn()
{
	turn = !turn;
}

Tile* Player::tileFromRack(int index)
{
	return(rack->getTile(index));
}

vector<Tile*> Player::placeTileStr(string str, Board* b, int r, int c, char dir)
{
	for(char& c : str) {
		c = toupper(c);
	}

	vector<Tile*> tileStrVec = rack->getTileStrVec(str);

	b->placeTileStr(rack, tileStrVec, r, c, dir);

	return tileStrVec;
}

bool Player::rackIsEmpty()
{
	return rack->isEmpty();
}

void Player::returnToRack(Tile* t, Board* b)
{
	if(t) {
		rack->addTile(b->retrieve(t->getSquare()->getRow(), t->getSquare()->getCol()));
	}
}
