/**
  * @file
  */
#ifndef GAME_H
#define GAME_H
#include <vector>
#include <string>

class Board;
class Bag;
class Player;
class Play;

/**
 * Implements the main game loop, logging and other functionalities
 */
class Game {
private:
	Board* gameBoard;
	Bag* gameBag;
	std::vector<Player*> players;
	std::vector<Play*> plays;
	std::string gameID;
	std::string logFilePath;
	void init();
	bool firstTurnCheck(std::string str, int r, int c, char dir);
	void addPlayer(Player* p);
	std::string getInput();
	void printHelp();

public:
	Game();
	~Game();

	void run();

};

#endif
