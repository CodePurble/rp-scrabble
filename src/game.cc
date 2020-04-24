#include "game.h"
#include "bag.h"
#include "board.h"
#include "player.h"
#include "utils.h"

using namespace std;

Game::Game()
{
	gameBoard = new Board;
	gameBag = new Bag;

	// Start 2 player game by default
	for(int i = 0; i < 2; i++){
		addPlayer(new Player(to_string(i)));
		players[i]->draw(7, gameBag);
	}
}

Game::~Game()
{
	if(gameBag)
		delete gameBag;

	if(gameBoard)
		delete gameBoard;

	for(Player* p : players){
		if(p)
			delete p;
	}
}

void Game::addPlayer(Player* p)
{
	if(p)
		players.push_back(p);
}

void Game::run()
{
	// while(!gameBag->bag.isEmpty()){
	//     gameBoard->show()
	//     for(Player* p : players){
    //
	//     }
	// }
}
