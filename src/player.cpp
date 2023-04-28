/**
  * @file
  */
#include <iostream>
#include <string>
#include "player.h"
#include "bag.h"
#include "tile.h"
#include "rack.h"
#include "board.h"
#include "utils.h"

using namespace std;

/**
  * Construct a Player
  *
  * @param n Name of Player
  *
  * This function shall not throw exceptions
  */
Player::Player(string n)
{
    score = 0;
    turn = false;
    playerName = n;
    rack = new Rack();
}

/**
  * Remove rack pointer
  */
Player::~Player()
{
    delete rack;
}

/**
 * "Pretty print" the Player object
 */
void Player::show(const char *window_title, int flags, FontCollection_t *fonts)
{
    rack->show(window_title, turn, flags, fonts->title);
    ImGui::Begin(window_title, nullptr, flags);
    ImGui::Text("%s: %d Points", playerName.c_str(), score);
    ImGui::Separator();
    ImGui::End();
}

/**
 * Show players score, with appropriate formatting
 */
void Player::showScore()
{
    if(turn) {
        BOLD_BRIGHT_GREEN_FG(" " + playerName + ": " + to_string(score) + " points");
    }
    else {
        BOLD_WHITE_FG(" " + playerName + ": " + to_string(score) + " points");
    }
}

/**
 * Getter for member playerName
 *
 * This function shall not throw exceptions.
 */
string Player::getName()
{
    return playerName;
}

/**
 * Getter for member score
 *
 * These functions shall not throw exceptions.
 */
int Player::getScore()
{
    return score;
}

/**
 * Set player name
 *
 * @param name The name of the player
 *
 * This function shall not throw exceptions.
 */
void Player::setName(std::string name)
{
    playerName = name;
}

/**
 * Update the Player's score
 *
 * @param points Points to add to current score
 *
 * This function shall not throw exceptions.
 */
void Player::updateScore(int points)
{
    score += points;
}

/**
 * Draw new Tiles from the Bag
 *
 * @param count Number of Tiles to draw
 * @param b Pointer to the Bag from which to draw from
 *
 * This function shall not throw exceptions.
 */
void Player::draw(int count, Bag* b)
{
    rack->fill(b->draw(count));
}

/**
 * Place a Tile on the Board
 *
 * @param t Pointer to the Tile to be placed
 * @param b Pointer of Board to place on
 * @param r Row where Square to be returned is
 * @param c Column where Square to be returned is
 *
 * @throws std::string containing the error message
 *
 * @return true if successful, false otherwise
 *
 * @note This function is a simple pass-through to the implementation in Board
 */
bool Player::placeTile(Tile* t, Board* b, int r, int c)
{
    return(b->placeTile(t, r, c));
}

/**
 * Toggle the "turn" data member
 *
 * This function shall not throw exceptions.
 */
void Player::toggleTurn()
{
    turn = !turn;
}

void Player::setTurn(bool status)
{
    turn = status;
}

/**
 * Get a Tile from the Players rack
 *
 * @param index Numerical index of the position of the Tile to get
 *
 * @return Pointer to the requested Tile, nullpointer if not found
 *
 * This function shall not throw exceptions.
 *
 * @note This function is redundant
 */
Tile* Player::tileFromRack(int index)
{
    return(rack->getTile(index));
}

/**
 * Place a series of Tiles on the Board
 *
 * @param str A string of letters that represent Tiles
 * @param b Pointer to the Board where the Tiles must be placed
 * @param r Row where the first Tile goes
 * @param c Column where the first Tile goes
 * @param dir Direction of placement ('h'/'v')
 *
 * @throws std::string containing error message
 */
vector<Tile*> Player::placeTileStr(string str, Board* b, int r, int c, char dir)
{
    for(char& c : str) {
        c = toupper(c);
    }

    vector<Tile*> tileStrVec = rack->getTileStrVec(str);

    b->placeTileStr(rack, tileStrVec, r, c, dir);

    return tileStrVec;
}

/**
 * Check if the player's rack is empty
 *
 * @return true if empty, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Player::rackIsEmpty()
{
    return rack->isEmpty();
}

/**
 * Return a Tile from the Board to the player's rack
 *
 * @param t Pointer to the Tile to be retrieved
 * @param b Pointer to the Board from which to retrieve
 *
 * This function shall not throw exceptions.
 */
void Player::returnToRack(Tile* t, Board* b)
{
    if(t) {
        rack->addTile(b->retrieve(t->getSquare()->getRow(), t->getSquare()->getCol()));
    }
}
