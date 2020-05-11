#include <iostream>
#include <ctime>
#include <string>
#include "game.h"
#include "bag.h"
#include "board.h"
#include "player.h"
#include "utils.h"
#include "play.h"
#include "tile.h"

using namespace std;

Game::Game()
{
	char filenameBuffer[60];
	time_t rawTime;
	time(&rawTime);
	strftime(filenameBuffer, 60, "-%F-scrabble.log", localtime(&rawTime));
	gameID = RawTimeToString(rawTime);
	logFilePath = "logs/" + gameID + string(filenameBuffer);

	DEBUG(" logFilePath", logFilePath);

	gameBoard = new Board;
	gameBag = new Bag;

	// Solitaire game by default
	addPlayer(new Player(to_string(1)));
}

Game::~Game()
{
	if(gameBag) {
		delete gameBag;
	}

	if(gameBoard) {
		delete gameBoard;
	}

	for(Player* p : players) {
		if(p) {
			delete p;
		}
	}
}

void Game::addPlayer(Player* p)
{
	if(p) {
		players.push_back(p);
	}
}

void Game::init()
{
	string tempName;
	char response;
	int i, j;
	bool complete = false;

	BOLD(" Welcome to Scrabble!");
	cout << "\n";

	for(Player* p : players) {
		cout << " Name of Player " + p->getName() + ": ";
		cin >> tempName;
		log(logFilePath, "Player 1: "+ tempName);
		p->setName(tempName);
	}

	cout << " Would you like to add more players? (y/n)? ";
	cin >> response;
	if(response == 'y') {
		while(!complete) {
			cout << " How many more (max 3 more)? ";
			cin >> i;
			if(i > 0 && i < 4) {
				for(j = 0; j < i; j++) {
					cout << " Name of Player " + to_string(j + i + 1) + ": ";
					cin >> tempName;
					addPlayer(new Player(tempName));
					log(logFilePath, "Player " + to_string(j + i + 1) + ": " + tempName);
				}
				complete = true;
			}
			else {
				if(i != 0) {
					BOLD(" You can only add upto 3 more players!\n");
				}
				else {
					break;
				}
			}
		}
	}
	cout << "\n";
}

bool Game::firstTurnCheck(string tileStr, int row, int col, char dir)
{
	if(dir == 'h') {
		for(int j = col; j < col + tileStr.length(); j++) {
			if(j == 7 && row == 7) {
				return true;
			}
		}
	}
	else if(dir == 'v') {
		for(int i = row; i < row + tileStr.length(); i++) {
			if(i == 7 && col == 7) {
				return true;
			}
		}
	}

	return false;
}

void Game::run()
{
	int row, col;
	bool endTurn;
	bool allEmpty = false;
	bool playValid;
	string tileStr, in;
	char dir;
	vector<string> parsed;

	init();

	for(Player* p : players) {
		p->draw(7, gameBag);
	}
	log(logFilePath, "Game start\n");

	// Main game loop
	while(!allEmpty) {
		for(Player* currPlayer : players) {
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
			for(Player* p : players) {
				p->show();
			}

			while(!endTurn) {
				try {
					BOLD(" " + currPlayer->getName());
					cout << " Enter your play (? for help) ";
					cin >> in;

					if(in == "?") {
						PALE_GREEN("\n A square is denoted by the pair (row, column)\n\n");
						PALE_GREEN(" Plays are denoted as follows-\n");
						PALE_GREEN(" <tiles>-<row>-<column>-<direction>\n");
						PALE_GREEN(" e.g. hat-4-6-v means that the tiles 'h', 'a' and 't' should be placed vertically and the first tile ('h') should be placed at (4, 6)\n\n");
						// PALE_GREEN(" If you have a blank tile (#) and you want to use it, you must give what letter it should be used as in the play\n");
						// PALE_GREEN(" e.g. a#nt-5-6-h implies that the '#' must be considered as the letter 'n'. The rest of the play is standard\n\n");
					}
					else {
						vector<vector<Tile*>> connnectedWords;
						vector<Tile*> tileStrVec;

						log(logFilePath, in);

						parsed = parsePlay(in);
						tileStr = parsed[0];
						row = stoi(parsed[1]);
						col = stoi(parsed[2]);
						dir = parsed[3][0];
						playValid = currPlay->validate(tileStr, gameBoard, row, col, dir);

						if(plays.size() == 1) {
							if(!firstTurnCheck(tileStr, row, col, dir)) {
								BOLD_RED(" This is the first turn of the game, please make sure the centre square is covered by your word\n");
							}
							else {
								playValid = true;
							}
						}

						if(playValid) {
							tileStrVec = currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
							connnectedWords = currPlay->getWords(tileStrVec, gameBoard, row, col, dir);
							currPlay->calculatePoints(connnectedWords);

							for(vector<Tile*> vec : connnectedWords) {
								for(Tile* t : vec) {
									t->getSquare()->show();
								}
								cout << "\n";
							}

							currPlayer->updateScore(currPlay->getPointsMade());

							currPlayer->draw(tileStr.length(), gameBag);
							currPlayer->toggleTurn();
							endTurn = !endTurn; // Turn ends
						}
						else {
							BOLD_RED(" You can't place a word there!\n");
						}
					}
				}
				catch(string ex) {
					BOLD_RED(" Error: " + ex);
				}
			}
			// Check whether all racks are empty
			for(Player* p : players) {
				allEmpty = allEmpty && p->rackIsEmpty();
			}
		}
	}

	BOLD(" You have placed all tiles!!! Final scores are-\n");
	for(Player* p : players) {
		p->show();
	}
}
