#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Rack;
class Bag;
class Tile;
class Board;

class Player {
	private:
		int score;
		bool turn;
		std::string playerName;
		Rack* rack;

	public:
		Player(std::string n);
		~Player();

		std::string getName();
		void setName(std::string);
		void toggleTurn();
		void updateScore(int points);
		Tile* tileFromRack(int index);

		bool placeTile(Tile* t, Board* b, int r, int c);
		bool placeTileStr(std::string str, Board* b, int r, int c, char dir);
		void draw(int count, Bag* b);
		void show();
};

#endif
