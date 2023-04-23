/**
  * @file
  */
#ifndef PLAY_H
#define PLAY_H
#include <string>
#include <vector>
#include "logger.h"

/**
 * Implements a "play"
 *
 * A play is made when a player places a word on the board, adds the points receieved to their
 * score, and refills their rack.
 *
 * The Play class tracks all aspects of the placement of tiles by a player such as points earned,
 * words made, tiles placed, etc
 */

class Player;
class Board;
class Tile;
class Dict;

class Play {
private:
    int pointsMade;
    Player* playMaker;
    std::string playStr;
    std::vector<std::vector<Tile*>> wordsInPlay;
    std::vector<std::string> wordStringsInPlay;

public:
    Play(Player* p);
    ~Play();

    void setPlayer(Player* p);
    bool checkPlacement(std::string tileStr, Board* b, int r, int c, char dir);
    std::string checkWords(Dict *dictionary);
    std::vector<std::vector<Tile*>> getWords(std::vector<Tile*> tilesInStr, Board* b, int row, int col, char dir);
    std::vector<Tile*> getConnectedWord(Tile* t, char dir);
    void calculatePoints(std::vector<std::vector<Tile*>> words, std::vector<Tile*> tileStrVec);
    int getPointsMade();
    bool confirmPlay();
    void reset();
    void show();
    void log(Logger *logger);
};

#endif
