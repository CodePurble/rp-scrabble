/**
  * @file
  */
#ifndef BAG_H
#define BAG_H
#include <vector>
#include <algorithm>
#include <random>

class Tile;

/**
 * Implements the bag of tiles used in a traditional game of scrabble.
 *
 * The bag is a vector of pointers to Tile objects
 */
class Bag {
private:
    std::vector<Tile*> bag;
    std::random_device rand;
    std::default_random_engine rng;

public:
    Bag();
    ~Bag();

    void show();
    bool isEmpty();
    void shuffle();
    std::vector<Tile*> draw(int count);
    int remainingTiles();
    void add(std::vector<Tile*> tiles);

};

#endif
