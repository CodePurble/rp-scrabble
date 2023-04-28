/**
  * @file
  */
#ifndef RACK_H
#define RACK_H
#include <array>
#include <vector>
#include <string>
#include "utils.h"

class Tile;

/**
 * Implements a rack
 *
 * A rack is an std::array of pointers Tile objects
 */
class Rack {
private:
    std::array<Tile*, 7> rack;

public:
    Rack();
    ~Rack();

    Tile* getTile(char ch);
    std::vector<Tile*> getTileStrVec(std::string tileStr);

    void fill(std::vector<Tile*> t);
    void addTile(Tile* t);
    bool isEmpty();
    void show(const char *window_title, bool alt, int flags, ImFont *font);
};

#endif
