#include <iostream>
#include "player.h"
#include "utils.h"
using namespace std;

Player::Player()
{
	score = 0;
	rack = new Rack();
}

Player::~Player()
{
	delete rack;
}

void Player::show()
{
	cout << "Score:" << score << endl;
}
