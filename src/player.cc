#include <iostream>
#include "player.h"
#include "bag.h"
#include "tile.h"
#include "rack.h"
#include "utils.h"

using namespace std;

Player::Player(string n)
{
	score = 0;
	playerName = n;
	rack = new Rack();
}

Player::~Player()
{
	delete rack;
}

void Player::show()
{
	cout << playerName << " Score:" << score << endl;
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
