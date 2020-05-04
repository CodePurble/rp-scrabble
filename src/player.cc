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
	if(turn)
		BOLD_BRIGHT_GREEN(" " + playerName + ": " + to_string(score) + " points\n");
	else
		BOLD(" " + playerName + ": " + to_string(score) + " points\n");

	rack->show();
	cout << "\n";
}

string Player::getName()
{
	return playerName;
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

void Player::placeTileStr(string str, Board* b, int r, int c, char dir)
{
	for(char& c : str)
		c = toupper(c);

	b->placeTileStr(rack->getTileStrVec(str), r, c, dir);
}

