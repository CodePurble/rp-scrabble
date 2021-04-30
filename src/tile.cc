/**
  * @file
  */
#include <iostream>
#include "tile.h"
#include "bag.h"
#include "square.h"
#include "rack.h"

using namespace std;

/**
  * Construct a Tile
  *
  * @param l Letter on the Tile
  * @param p Point value of the Tile
  * @param p_loc Location of the Tile
  *
  * This function shall not throw exceptions
  */
Tile::Tile(char l, int p, enum_location p_loc)
{
    letter = l;
    points = p;
    presentLoc = p_loc;
    tBag = nullptr;
    tRack = nullptr;
    tSquare = nullptr;
}

/**
  * Copy constructor for Tile
  *
  * @param source Source to copy from
  *
  * This function shall not throw exceptions
  */
Tile::Tile(Tile& source)
{
    letter = source.letter;
    points = source.points;
    presentLoc = source.presentLoc;
}

/**
 * "Pretty print" a tile.
 * Used mostly for debug purposes
 */
void Tile::show()
{
    cout << letter << "-" << points << " ";
}

/**
 * Getter for member letter
 *
 * @return letter as char
 *
 * This function shall not throw exceptions.
 */
char Tile::getLetter()
{
    return letter;
}

/**
 * Getter for member letter
 *
 * @return points
 *
 * This function shall not throw exceptions.
 */
int Tile::getPoints()
{
    return points;
}

/**
 * Getter for member letter
 *
 * @return Tile location
 *
 * This function shall not throw exceptions.
 */
int Tile::getLoc()
{
    switch(presentLoc) {
    case BAG:
        return 0;
        break;
    case RACK:
        return 1;
        break;
    case BOARD:
        return 2;
        break;
    default:
        return -1;
    }
}

/**
 * Getter for member letter
 *
 * @return letter as std::string
 *
 * This function shall not throw exceptions.
 */
string Tile::getLetterStr()
{
    return string(1, letter);
}

/**
 * Getter for member tRack
 *
 * @return Pointer to rack that the tile is present in, nullptr if not in a rack
 *
 * This function shall not throw exceptions.
 */
Rack* Tile::getRack()
{
    return tRack;
}

/**
 * Getter for member tBag
 *
 * @return Pointer to the Bag that the Tile came from
 *
 * This function shall not throw exceptions.
 */
Bag* Tile::getBag()
{
    return tBag;
}

/**
 * Getter for member tSquare
 *
 * @return A pointer to the Square the Tile is placed in, nullptr if not in a Square
 *
 * This function shall not throw exceptions.
 */
Square* Tile::getSquare()
{
    return tSquare;
}

/**
 * Setter for member tBag
 *
 * @param b Pointer to a Bag
 *
 * This function shall not throw exceptions.
 */
void Tile::setBag(Bag* b)
{
    tBag = b;
    setLoc(0);
}

/**
 * Setter for member tBag
 *
 * @param r Pointer to a Rack
 *
 * This function shall not throw exceptions.
 */
void Tile::setRack(Rack* r)
{
    tRack = r;
    setLoc(1);
}

/**
 * Setter for member tBag
 *
 * @param loc a valid value from enum_location
 *
 * @throws std::string containing the error message
 */
void Tile::setLoc(int loc)
{
    switch(loc) {
    case 0:
        presentLoc = BAG;
        break;
    case 1:
        presentLoc = RACK;
        break;
    case 2:
        presentLoc = BOARD;
        break;
    default:
        throw(string("Invalid value of type enum_location\n"));
    }
}

/**
 * Setter for member tBag
 *
 * @param s Pointer to a Square
 *
 * This function shall not throw exceptions.
 */
void Tile::setSquare(Square* s)
{
    tSquare = s;
}
