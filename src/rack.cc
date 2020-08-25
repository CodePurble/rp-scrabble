/**
  * @file
  */
#include <iostream>
#include "rack.h"
#include "tile.h"
#include "utils.h"

using namespace std;

/**
  * Init rack with nullptr
  */
Rack::Rack()
{
	rack.fill(nullptr);
}

/**
  * Clean up rack
  */
Rack::~Rack()
{
	for(Tile* t : rack) {
		if(t) {
			delete t;
		}
	}
}

/**
 * "Pretty print" the rack
 */
void Rack::show()
{
	int rackSize = rack.size();

	cout << " ";
	for(int i = 0; i < rackSize; i++) {
		BOARD_COLOURS("+-----");
	}

	BOARD_COLOURS("+");
	cout << "\n";
	cout << " ";
	BOARD_COLOURS("| ");

	for(unsigned long i = 0; i < rack.size(); i++) {
		if(rack[i]) {
			TILE_COLOURS(" " + rack[i]->getLetterStr() + " ");
		}
		else {
			BOARD_COLOURS("   ");
		}
		if(i == 6) {
			BOARD_COLOURS(" |");
		}
		else {
			BOARD_COLOURS(" | ");
		}
	}
	cout << "\n" << " ";
	for(int i = 0; i < rackSize; i++) {
		BOARD_COLOURS("+-----");
	}

	BOARD_COLOURS("+");
	cout << "\n";
}

/**
 * Request a Tile from the rack
 *
 * @param ch Character representing the Tile
 *
 * @return Pointer to the requested Tile if the Tile exists, nullptr otherwise
 *
 * This function shall not throw exceptions
 */
Tile* Rack::getTile(char ch)
{
	for(Tile* t : rack) {
		if(t) {
			if(t->getLetter() == ch) {
				return t;
			}
		}
	}
	return nullptr;
}

/**
 * Fill the rack with provided tiles
 *
 * @param t A vector of pointers to the Tiles to be put in the rack
 *
 * This function shall not throw exceptions.
 */
void Rack::fill(vector<Tile*> t)
{
	unsigned long i = 0;
	while(!t.empty() && i < rack.size()) {
		if(!rack[i]) {
			rack[i] = t.back();
			rack[i]->setLoc(1);
			rack[i]->setRack(this);
			t.pop_back();
		}
		i++;
	}
}

/**
 * Add a Tile to the rack
 *
 * @param t A pointer to the Tile to be placed in the rack
 *
 * This function shall not throw exceptions.
 */
void Rack::addTile(Tile* t)
{
	for(unsigned long i = 0; i < rack.size(); i++) {
		if(!rack[i]) {
			rack[i] = t;
			rack[i]->setLoc(1);
			rack[i]->setRack(this);
			break;
		}
	}
}

/**
 * Get a vector of the Tiles requested from the rack
 *
 * @param tileStr A string of letters that represent Tiles
 *
 * @return A vector of pointers to the requested Tiles
 *
 * @throws std::string containing the error message
 */
vector<Tile*> Rack::getTileStrVec(string tileStr)
{
	vector<Tile*> tileStrVec;
	bool found;

	for(char ch : tileStr) {
		found = false;
		for(auto& t: rack) {
			if(t && ch == t->getLetter()) {
				found = true;
				tileStrVec.push_back(t);
				t = nullptr; // "Remove" from rack
				break;
			}
		}
		if(!found) {
			// Abort!! Reset the rack and start again
			fill(tileStrVec);
			throw string(string(1, ch) + " not found\n");
		}
	}
	return tileStrVec;
}

/**
 * Check whether rack is empty
 *
 * @return true if empty, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Rack::isEmpty()
{
	for(unsigned long i = 0; i < rack.size(); i++) {
		if(rack[i]) {
			return false;
		}
	}
	return true;
}
