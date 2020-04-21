#ifndef PLAYER_H
#define PLAYER_H
#include "rack.h"

class Player {
	private:
		int score;
		Rack* rack;

	public:
		Player();
		~Player();
		void show();
};

#endif
