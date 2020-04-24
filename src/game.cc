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

	// 2 player game by default
	for(int i = 0; i < 2; i++){
		addPlayer(new Player(to_string(i)));
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

void Game::init()
{
	string tempName;
	char response;
	int i, j;

	BOLD(" Welcome to Scrabble!");
	cout << "\n";

	for(i = 0; i < 2; i++){
		cout << " Name of Player " + to_string(i+1) + ": ";
		cin >> tempName;
		players[i]->setName(tempName);
	}

	cout << " Would you like to add more players? (y/n)? ";
	cin >> response;
	if(response == 'y'){
		cout << " How many more (max 2)? ";
		cin >> i;
		for(j = 0; j < i; j++){
			cout << " Name of Player " + to_string(j + i + 2) + ": ";
			cin >> tempName;
			addPlayer(new Player(tempName));
		}
	}
	cout << "\n";
}

void Game::run()
{
	init();

	for(Player* p : players){
		p->draw(7, gameBag);
	}

	// Main game loop
	while(!gameBag->isEmpty()){
		for(Player* currPlayer : players){
			int tileIndex, row, col, tileCount;
			bool endTurn = false;

			currPlayer->toggleTurn(); // Turn begins
			gameBoard->show();
			currPlayer->show();
			for(Player* others : players){
				if(others != currPlayer)
					others->show();
			}

			tileCount = 0;
			while(!endTurn){
				cout << " " + currPlayer->getName() + ", choose a tile to place" << endl;
				cout << "(select tile by entering its corresponding number or press '99' to end your turn) ";
				cin >> tileIndex;
				if(tileIndex != 99){
					cout << " Where to place it? ";
					cin >> row >> col;
					if(!currPlayer->placeTile(currPlayer->tileFromRack(tileIndex), gameBoard, row, col))
						// TODO Put tile back in rack if cannot place (don't set tile to null until
						// successfully placed
						BOLD_RED(" Can't place a tile there!!\n");
					else{
						gameBoard->show();
						currPlayer->show();
						tileCount++;
					}
				}
				else
					endTurn = !endTurn;
			}
			currPlayer->draw(tileCount, gameBag);
			currPlayer->toggleTurn(); // Turn ends
		}
	}
}
