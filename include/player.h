/**
  * @file
  */
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

class Rack;
class Bag;
class Tile;
class Board;

/**
 * Implements a player
 *
 * Each player has a name, a rack, and a score associated with them
 */
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
    int getScore();
    Tile* tileFromRack(int index);

    bool placeTile(Tile* t, Board* b, int r, int c);
    std::vector<Tile*> placeTileStr(std::string str, Board* b, int r, int c, char dir);
    void draw(int count, Bag* b);
    bool rackIsEmpty();
    void returnToRack(Tile* t, Board* b);
    void showScore();
    void show();
};

#endif
