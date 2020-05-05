#include <iostream>
#include "game.h"
#include "bag.h"
#include "board.h"
#include "player.h"
#include "utils.h"
#include "play.h"

using namespace std;

Game::Game()
{
	gameBoard = new Board;
	gameBag = new Bag;

	// Solitaire game by default
	addPlayer(new Player(to_string(1)));
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

	for(Player* p : players){
		cout << " Name of Player " + p->getName() + ": ";
		cin >> tempName;
		p->setName(tempName);
	}

	cout << " Would you like to add more players? (y/n)? ";
	cin >> response;
	if(response == 'y'){
		cout << " How many more (max 3 more)? ";
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
	string tileStr, in;
	char dir;
	vector<string> parsed;

	init();

	for(Player* p : players){
		p->draw(7, gameBag);
	}

	// Main game loop
	while(!gameBag->isEmpty()){
		for(Player* currPlayer : players){
			plays.push_back(new Play(currPlayer));
			Play* currPlay = plays.back();
			row = col = 7;
			endTurn = false;
			tileStr = "";

			currPlayer->toggleTurn(); // Turn begins
			gameBoard->show();
			BOLD(" Bag: ");
			gameBag->show();
			cout << "\n";
			for(Player* p : players){
					p->show();
			}

			while(!endTurn){
				try{
					if(plays.size() == 1){
						BOLD(" " + currPlayer->getName());
						cout << ", enter the word you want to place" << endl << " ";
						cin >> tileStr;

						cout << " This is the first turn, so the first tile of your word goes in the middle\n";

						cout << " Horizontal or vertical? ";
						cin >> dir;

						currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
						currPlayer->draw(tileStr.length(), gameBag);
						currPlayer->toggleTurn();
						endTurn = !endTurn; // Turn ends
					}
					else{
						BOLD(" " + currPlayer->getName());
						cout << " Enter your play (e.g. bag-5-5-h) ";
						cin >> in;
						parsed = parsePlay(in);
						tileStr = parsed[0];
						row = stoi(parsed[1]);
						col = stoi(parsed[2]);
						dir = parsed[3][0];
						// cout << ", enter the word you want to place" << endl << " ";
						// cin >> tileStr;
                        //
						// cout << " Where does the first tile go? ";
						// cin >> row >> col;
                        //
						// cout << " Horizontal or vertical? ";
						// cin >> dir;

						if(currPlay->validate(tileStr, gameBoard, row, col, dir)){
							currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
							currPlayer->draw(tileStr.length(), gameBag);
							currPlayer->toggleTurn();
							endTurn = !endTurn; // Turn ends
						}
						else{
							BOLD_RED(" You can't place a word there!\n");
						}
					}
				}
				catch(string ex){
					BOLD_RED(" Error: " + ex);
				}
			}
		}
	}
}
