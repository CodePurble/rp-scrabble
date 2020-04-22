#ifndef PLAYER_H
#define PLAYER_H
#include "rack.h"

class Player {
	private:
		int score;
		std::string playerName;
		Rack* rack;

	public:
		Player(std::string n);
		~Player();

		void placeTile(Tile* t, int r, int c);
		void show();
};

#endif
