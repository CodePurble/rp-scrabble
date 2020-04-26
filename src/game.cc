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
	int row, col;
	bool endTurn;
	string tileStr;
	char dir;

	init();

	for(Player* p : players){
		p->draw(7, gameBag);
	}

	// Main game loop
	while(!gameBag->isEmpty()){
		for(Player* currPlayer : players){
			row = col = 0;
			endTurn = false;
			tileStr = "";

			currPlayer->toggleTurn(); // Turn begins
			gameBoard->show();
			for(Player* p : players){
					p->show();
			}

			while(!endTurn){
				try{
					cout << " " + currPlayer->getName() + ", enter the word you want to place" << endl << " ";
					cin >> tileStr;

					cout << " Where does the first tile go? ";
					cin >> row >> col;

					cout << " Horizontal or vertical? ";
					cin >> dir;

					currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
					currPlayer->draw(tileStr.length(), gameBag);
					currPlayer->toggleTurn();
					endTurn = !endTurn; // Turn ends
				}
				catch(string ex){
					BOLD_RED("Error: " + ex);
				}
			}
		}
	}
}
