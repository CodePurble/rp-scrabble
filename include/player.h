#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Rack;
class Bag;
class Tile;

class Player {
	private:
		int score;
		std::string playerName;
		Rack* rack;

	public:
		Player(std::string n);
		~Player();

		std::string getName();
		void setName(std::string);
		void updateScore(int points);

		void placeTile(Tile* t, int r, int c);
		void draw(int count, Bag* b);
		void show();
};

#endif
