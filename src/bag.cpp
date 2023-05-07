/**
  * @file
  */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "bag.h"
#include "tile.h"
#include "utils.h"

using namespace std;

enum_location loc = BAG;

/**
 * Bag constructor
 * "Fills" the bag member vector with "Tiles"
 */
Bag::Bag()
{
    rng = std::default_random_engine{rand()};
    Tile* curTile = nullptr;
    /* Add a's */
    for(int i = 0; i < 9; i++) {
        curTile = new Tile('A', 1, loc);
        bag.push_back(curTile);
    }

    /* Add b's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('B', 3, loc);
        bag.push_back(curTile);
    }

    /* Add c's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('C', 3, loc);
        bag.push_back(curTile);
    }

    /* Add d's */
    for(int i = 0; i < 4; i++) {
        curTile = new Tile('D', 2, loc);
        bag.push_back(curTile);
    }

    /* Add e's */
    for(int i = 0; i < 12; i++) {
        curTile = new Tile('E', 1, loc);
        bag.push_back(curTile);
    }

    /* Add f's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('F', 4, loc);
        bag.push_back(curTile);
    }

    /* Add g's */
    for(int i = 0; i < 3; i++) {
        curTile = new Tile('G', 2, loc);
        bag.push_back(curTile);
    }

    /* Add h's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('H', 4, loc);
        bag.push_back(curTile);
    }

    /* Add i's */
    for(int i = 0; i < 9; i++) {
        curTile = new Tile('I', 1, loc);
        bag.push_back(curTile);
    }

    /* Add j */
    curTile = new Tile('J', 8, loc);
    bag.push_back(curTile);

    /* Add k */
    curTile = new Tile('K', 5, loc);
    bag.push_back(curTile);

    /* Add l's */
    for(int i = 0; i < 4; i++) {
        curTile = new Tile('L', 1, loc);
        bag.push_back(curTile);
    }

    /* Add m's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('M', 3, loc);
        bag.push_back(curTile);
    }

    /* Add n's */
    for(int i = 0; i < 6; i++) {
        curTile = new Tile('N', 1, loc);
        bag.push_back(curTile);
    }

    /* Add o's */
    for(int i = 0; i < 8; i++) {
        curTile = new Tile('O', 1, loc);
        bag.push_back(curTile);
    }

    /* Add p's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('P', 3, loc);
        bag.push_back(curTile);
    }

    /* Add q */
    curTile = new Tile('Q', 10, loc);
    bag.push_back(curTile);

    /* Add r's */
    for(int i = 0; i < 6; i++) {
        curTile = new Tile('R', 1, loc);
        bag.push_back(curTile);
    }

    /* Add s's */
    for(int i = 0; i < 4; i++) {
        curTile = new Tile('S', 1, loc);
        bag.push_back(curTile);
    }

    /* Add t's */
    for(int i = 0; i < 6; i++) {
        curTile = new Tile('T', 1, loc);
        bag.push_back(curTile);
    }

    /* Add u's */
    for(int i = 0; i < 4; i++) {
        curTile = new Tile('U', 3, loc);
        bag.push_back(curTile);
    }

    /* Add v's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('V', 4, loc);
        bag.push_back(curTile);
    }

    /* Add w's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('W', 4, loc);
        bag.push_back(curTile);
    }
    /* Add x */
    curTile = new Tile('X', 8, loc);
    bag.push_back(curTile);

    /* Add y's */
    for(int i = 0; i < 2; i++) {
        curTile = new Tile('Y', 4, loc);
        bag.push_back(curTile);
    }

    /* Add z */
    curTile = new Tile('Z', 10, loc);
    bag.push_back(curTile);

    /*
     * [> Add blanks <]
     * for(int i = 0; i < 2; i++){
     *     curTile = new Tile('#', 0, loc);
     *     bag.push_back(curTile);
     * }
     */

    for(auto& t : bag) {
        t->setBag(this);
    }
}

/**
 * Bag destructor
 */
Bag::~Bag()
{
    for(Tile* t : bag) {
        delete t;
    }

    bag.clear();
}

/**
 * "Pretty print" the Bag.
 */
void Bag::show()
{
    for(Tile* i : bag) {
        cout << i->getLetter();
    }
    BOLD(" (" + to_string(bag.size()) + " tiles remaining)\n");
}

/**
 * "Shuffle" the Tiles in the Bag.
 *
 * Does so by swapping Tiles in the vector to random indices.
 */
void Bag::shuffle()
{
    std::shuffle(begin(bag), end(bag), rng);
}

/**
 * Draw specified number of Tiles from the Bag.
 *
 * @param count The number of Tiles to draw.
 *
 * @return drawn A vector of pointers to the drawn Tiles.
 *
 * This function shall not throw exceptions.
 */
vector<Tile*> Bag::draw(int count)
{
    vector<Tile*> drawn;
    unsigned long prev_size = bag.size();

    shuffle();

    for(unsigned long i = 0; i < (unsigned long) count && i < prev_size; i++) {
        drawn.push_back(bag.back());
        bag.pop_back();
    }
    return drawn;
}

/**
 * Check if bag is empty
 *
 * @return true if empty, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Bag::isEmpty()
{
    return(bag.empty());
}

int Bag::remainingTiles()
{
    return(bag.size());
}
