#include <iostream>
#include "player.h"
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
