#ifndef GAME_H
#define GAME_H
#include <vector>

class Board;
class Bag;
class Player;
class Play;

class Game {
	private:
		Board* gameBoard;
		Bag* gameBag;
		std::vector<Player*> players;
		std::vector<Play*> plays;
		void init();

	public:
		Game();
		~Game();

		void addPlayer(Player* p);
		void run();

};

#endif
