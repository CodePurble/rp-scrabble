/**
  * @file
  */
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "game.h"
#include "bag.h"
#include "board.h"
#include "player.h"
#include "utils.h"
#include "play.h"
#include "tile.h"

using namespace std;

/**
  * Initialise all data required for a Game, including log-files, gameID
  */
Game::Game()
{
    char filenameBuffer[60];
    time_t rawTime;
    time(&rawTime);
    strftime(filenameBuffer, 60, "-%F-scrabble.log", localtime(&rawTime));
    gameID = RawTimeToString(rawTime);
    logFilePath = LOG_PATH + gameID + string(filenameBuffer);

    // DEBUG_PRINT(" logFilePath", logFilePath);
    cout << endl;

    gameBoard = new Board;
    gameBag = new Bag;

    // Solitaire game by default
    addPlayer(new Player(to_string(1)));
}

/**
  * Clean up game data
  */
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

/**
 * Add a Player to the Game
 *
 * @param p Pointer to the new Player
 *
 * This function shall not throw exceptions.
 */
void Game::addPlayer(Player* p)
{
    if(p) {
        players.push_back(p);
    }
}

/**
 * Initialise and set up the game
 */
void Game::init()
{
    string tempName;
    char response;
    int i, j;
    bool complete = false;

    try {
        log(logFilePath, "Log start\n");
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }

    BOLD(" Welcome to Scrabble!");
    cout << "\n";

    for(Player* p : players) {
        cout << " Name of Player " + p->getName() + ": ";
        cin >> tempName;
        try {
            log(logFilePath, "Player 1: "+ tempName);
        }
        catch(string err) {
            BOLD_RED_FG(" " + err);
            BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
            BOLD_RED_FG(" Aborting\n");
            exit(1);
        }
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
                    cout << " Name of Player " + to_string(j + 2) + ": ";
                    cin >> tempName;
                    addPlayer(new Player(tempName));
                    try {
                        log(logFilePath, "Player " + to_string(j + i) + ": " + tempName);
                    }
                    catch(string err) {
                        BOLD_RED_FG(" " + err);
                        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
                        BOLD_RED_FG(" Aborting\n");
                        exit(1);
                    }
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
    else if(response == 'n') {
        // do nothing, carry on
    }
    else {
        BOLD_RED_FG(" Error: Invalid input\n");
        init();
    }
    cout << "\n";
}

/**
 * Check whether the first play is valid
 *
 * @param tileStr String of letters that represent the Tiles to be placed
 * @param r Row where the first Tile goes
 * @param c Column where first tile goes
 * @param dir Direction of placement
 *
 * @return true if valid, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Game::firstTurnCheck(string tileStr, int row, int col, char dir)
{
    if(dir == 'h') {
        for(unsigned long j = col; j < col + tileStr.length(); j++) {
            if(j == 7 && row == 7) {
                return true;
            }
        }
    }
    else if(dir == 'v') {
        for(unsigned long i = row; i < row + tileStr.length(); i++) {
            if(i == 7 && col == 7) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Used to take user input
 *
 * @return User input as a std::string
 *
 * @throws std::invalid_argument For integer inputs
 * @throws std::string containing the error message for other inputs
 */
string Game::getInput()
{
    string tempIn = "";
    string input = "";

    BOLD(" Enter the tiles you want to place ");
    cout << "(? for help, - to quit) ";
    cin >> tempIn;
    if(tempIn == "?") {
        return "?";
    }
    else if(tempIn == ".") {
        return ".";
    }
    else if(tempIn == "-") {
        return "-";
    }
    else if(tempIn == "!") {
        return "!";
    }
    else if(tempIn == "#") {
        return "#";
    }
    else {
        for(char ch : tempIn) {
            if(!charPresent(alphabets, ch)) {
                throw(string("Invalid character input\n"));
            }
        }
        input.append(tempIn + "-");
    }

    BOLD(" Enter the row where the first tile will go ");
    cout << "(? for help, - to quit) ";
    cin >> tempIn;
    if(tempIn == "?") {
        return "?";
    }
    else if(tempIn == ".") {
        return ".";
    }
    else if(tempIn == "-") {
        return "-";
    }
    else if(tempIn == "!") {
        return "!";
    }
    else if(tempIn == "#") {
        return "#";
    }
    else {
        try {
            stoi(tempIn);
        }
        catch(const invalid_argument& ia) {
            throw(string("Invalid integer input\n"));
        }
        input.append(tempIn + "-");
    }

    BOLD(" Enter the column where the first tile will go ");
    cout << "(? for help, - to quit) ";
    cin >> tempIn;
    if(tempIn == "?") {
        return "?";
    }
    else if(tempIn == ".") {
        return ".";
    }
    else if(tempIn == "-") {
        return "-";
    }
    else if(tempIn == "!") {
        return "!";
    }
    else if(tempIn == "#") {
        return "#";
    }
    else {
        try {
            stoi(tempIn);
        }
        catch(const invalid_argument& ia) {
            throw(string("Invalid integer input"));
        }
        input.append(tempIn + "-");
    }

    BOLD(" Enter the direction of placement ");
    cout << "(? for help, - to quit) ";
    cin >> tempIn;
    if(tempIn == "?") {
        return "?";
    }
    else if(tempIn == ".") {
        return ".";
    }
    else if(tempIn == "-") {
        return "-";
    }
    else if(tempIn == "!") {
        return "!";
    }
    else if(tempIn == "#") {
        return "#";
    }
    else {
        if(tempIn.length() != 1 && (tempIn != "h" || tempIn != "v")) {
            throw(string("Invalid direction\n"));
        }
        input.append(tempIn);
    }

    return input;
}

/**
 * Print help information
 *
 * This function shall not throw exceptions.
 */
void Game::printHelp()
{
    PALE_GREEN_FG("\n The tiles you want to place are entered in order of placement using the respective letter\n\n");
    PALE_GREEN_FG(" The row and column of the square to place can be seen outside the edge of the board\n\n");
    PALE_GREEN_FG(" The placement direction can either be 'v' (place tiles vertically downward one after the other) or\n");
    PALE_GREEN_FG(" 'h' (place tiles horizontally from left to right one after the other)\n\n");

    BOLD(" Commands\n");
    BOLD(" --------\n");

    BOLD_BRIGHT_GREEN_FG(" ? ");
    cout << "Show this help text\t";
    BOLD_BRIGHT_GREEN_FG(" . ");
    cout << "Show the board\t";
    BOLD_BRIGHT_GREEN_FG(" ! ");
    cout << "Skip turn\n";
    BOLD_BRIGHT_GREEN_FG(" # ");
    cout << "Show scores\t\t";
    BOLD_BRIGHT_GREEN_FG(" - ");
    cout << "Quit the game\n\n";

    BOLD(" Board legend\n");
    BOLD(" ------------\n");

    cout << " ";
    RED_BG("   ");
    cout << " Triple Word Score\t";

    cout << " ";
    PINK_BG("   ");
    cout << " Double Word Score\t";

    cout << " ";
    DARK_BLUE_BG("   ");
    cout << " Triple Letter Score\t";

    cout << " ";
    LIGHT_BLUE_BG("   ");
    cout << " Double Letter Score\n\n";
}

/**
 * Main game logic. Contains main game loop
 *
 * This function shall not throw exceptions.
 */
void Game::run()
{
    int row, col;
    bool endTurn;
    bool allEmpty = false;
    bool playValid;
    bool firstTurn = true;
    string tileStr;
    string in = "";
    string tempIn = "";
    char dir;
    vector<string> parsed;

    init();

    // Fill up all Players racks
    for(Player* p : players) {
        p->draw(7, gameBag);
    }

    try {
        log(logFilePath, "\nGame start\n");
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }

    // Main game loop
    while(!allEmpty) {
        for(Player* currPlayer : players) {
            if(!currPlayer->rackIsEmpty()) {
                plays.push_back(new Play(currPlayer));
                Play* currPlay = plays.back();
                row = col = 7;
                endTurn = false;
                tileStr = "";

                currPlayer->toggleTurn(); // Turn begins;
                gameBoard->show();
                BOLD(" Bag: ");
                gameBag->show();
                cout << "\n";
                currPlayer->show();

                while(!endTurn) {
                    try {
                        BOLD(" " + currPlayer->getName());

                        in = getInput();

                        if(in == "?") {
                            printHelp();
                        }
                        else if(in == ".") {
                            gameBoard->show();
                            BOLD(" Bag: ");
                            gameBag->show();
                            cout << "\n";
                            currPlayer->show();
                        }
                        else if(in == "-") {
                            char c;
                            BOLD_RED_FG(" Are you sure you want to quit? (y/n) ");
                            cin >> c;
                            if(c == 'y') {
                                for(Player* p : players) {
                                    log(logFilePath, p->getName() + ": " + to_string(p->getScore()));
                                }
                                exit(0);
                            }
                            else if(c == 'n') {
                                // Do nothing
                            }
                            else {
                                throw(string("Invalid input\n"));
                            }
                        }
                        else if(in == "!") {
                            char c;
                            BOLD_RED_FG(" Skip turn? (y/n) ");
                            cin >> c;
                            if(c == 'y') {
                                currPlayer->toggleTurn();
                                endTurn = !endTurn;
                            }
                            else if(c == 'n') {
                                // Do nothing
                            }
                            else {
                                throw(string("Invalid input\n"));
                            }
                        }
                        else if(in == "#") {
                            for(Player* p : players) {
                                p->showScore();
                                cout << "\t";
                            }
                            cout << "\n";
                        }
                        else {
                            vector<vector<Tile*>> connnectedWords;
                            vector<Tile*> tileStrVec;

                            try {
                                log(logFilePath, in);
                            }
                            catch(string err) {
                                BOLD_RED_FG(" " + err);
                                BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
                                BOLD_RED_FG(" Aborting\n");
                                exit(1);
                            }

                            parsed = parsePlay(in);

                            tileStr = parsed[0];
                            row = stoi(parsed[1]);
                            col = stoi(parsed[2]);
                            dir = parsed[3][0];
                            playValid = currPlay->validate(tileStr, gameBoard, row, col, dir);

                            if(firstTurn) {
                                if(!firstTurnCheck(tileStr, row, col, dir)) {
                                    firstTurn = true;
                                    BOLD_RED_FG(" This is the first turn of the game, please make sure the centre square is covered by your word\n");
                                }
                                else {
                                    playValid = true;
                                    firstTurn = false;
                                }
                            }

                            if(playValid) {
                                tileStrVec = currPlayer->placeTileStr(tileStr, gameBoard, row, col, dir);
                                connnectedWords = currPlay->getWords(tileStrVec, gameBoard, row, col, dir);
                                currPlay->calculatePoints(connnectedWords, tileStrVec);

                                currPlay->show();

                                if(currPlay->confirmPlay()) {
                                    currPlayer->updateScore(currPlay->getPointsMade());
                                    currPlayer->draw(tileStr.length(), gameBag);
                                    currPlayer->toggleTurn();
                                    endTurn = !endTurn; // Turn ends
                                }
                                else {
                                    for(Tile* t : tileStrVec) {
                                        currPlayer->returnToRack(t, gameBoard);
                                    }
                                    currPlay->reset();
                                }
                            }
                            else {
                                BOLD_RED_FG(" You can't place a word there!\n");
                            }
                        }
                    }
                    catch(string ex) {
                        BOLD_RED_FG(" Error: " + ex);
                    }
                }
            }
            // Find out whether all racks are empty
            allEmpty = players.front()->rackIsEmpty();
            for(Player* p : players) {
                allEmpty = allEmpty && p->rackIsEmpty();
            }
        }
    }

    BOLD(" You have placed all tiles!!! Final scores are-\n");
    for(Player* p : players) {
        log(logFilePath, "\n");
        log(logFilePath, p->getName() + ": " + to_string(p->getScore()) + "\n");
        BOLD_WHITE_FG(p->getName() + ": " + to_string(p->getScore()) + "\n");
    }
}
