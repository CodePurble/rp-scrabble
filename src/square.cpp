/**
  * @file
  */
#include <iostream>
#include "square.h"
#include "tile.h"

using namespace std;

/**
  * Construct a Square
  *
  * @param st Type of Square
  * @param r Row where the Square is on the Board
  * @param c Column where the Square is on the Board
  *
  * This function shall not throw exceptions
  */
Square::Square(enum_sqType st, int r, int c)
{
    sqType = st;
    tileInSquare = nullptr;
    left = right = above = below = nullptr;
    row = r;
    col = c;
}

/**
 * "Pretty print" the square object.
 * Primarily used for debug purposes
 */
void Square::show()
{
    if(!isEmpty()) {
        getTile()->show();
        cout << "in ";
        cout << sqType << " @ (" << row << "," << col << "), ";
    }
    else {
        cout << sqType << " @ (" << row << "," << col << "), ";
    }
}

/**
 * Getter for member left
 *
 * @return A pointer to the Square that is to the left of the calling object, nullptr if not present
 *
 * This function shall not throw exceptions.
 */
Square* Square::getLeft()
{
    return left;
}

/**
 * Getter for member right
 *
 * @return A pointer to the Square that is to the right of the calling object, nullptr if not present
 *
 * This function shall not throw exceptions.
 */
Square* Square::getRight()
{
    return right;
}

/**
 * Getter for member above
 *
 * @return A pointer to the Square that is above the calling object, nullptr if not present
 *
 * This function shall not throw exceptions.
 */
Square* Square::getAbove()
{
    return above;
}

/**
 * Getter for member below
 *
 * @return A pointer to the Square that is below the calling object, nullptr if not present
 *
 * This function shall not throw exceptions.
 */
Square* Square::getBelow()
{
    return below;
}

/**
 * Getter for member row
 *
 * @return row number
 *
 * This function shall not throw exceptions.
 */
int Square::getRow()
{
    return row;
}

/**
 * Getter for member col
 *
 * @return column number
 *
 * This function shall not throw exceptions.
 */
int Square::getCol()
{
    return col;
}

/**
 * Getter for member sqType
 *
 * @return type of Square
 *
 * @see square.h
 *
 * This function shall not throw exceptions.
 */
int Square::getType()
{
    return sqType;
}

/**
 * Check state of square
 *
 * @return true if empty, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Square::isEmpty()
{
    if(tileInSquare) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Setter for member tileInSquare
 * "Place" a Tile in a Square
 *
 * @param t Pointer to the Tile to pe "placed"
 *
 * This function shall not throw exceptions.
 */
void Square::setTile(Tile* t)
{
    tileInSquare = t;
}

/**
 * Getter for member tileInSquare
 *
 * @return A pointer to the Tile that is in the square, nullptr if empty
 *
 * This function shall not throw exceptions.
 */
Tile* Square::getTile()
{
    return tileInSquare;
}

/**
 * Setter for member left
 *
 * @param l A pointer to the Square to set
 *
 * This function shall not throw exceptions.
 */
void Square::setLeft(Square* l)
{
    left = l;
}

/**
 * Setter for member right
 *
 * @param r A pointer to the Square to set
 *
 * This function shall not throw exceptions.
 */
void Square::setRight(Square* r)
{
    right = r;
}

/**
 * Setter for member above
 *
 * @param u A pointer to the Square to set
 *
 * This function shall not throw exceptions.
 */
void Square::setAbove(Square* u)
{
    above = u;
}

/**
 * Setter for member below
 *
 * @param d A pointer to the Square to set
 *
 * This function shall not throw exceptions.
 */
void Square::setBelow(Square* d)
{
    below = d;
}

/**
 * Check if any neighbour Squares are present to the left, above or below
 *
 * @return true if found, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Square::checkNeighboursH()
{
    if(left || above || below) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Check if any neighbour Squares are present to the left, above or to the right
 *
 * @return true if found, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Square::checkNeighboursV()
{
    if(left || above || right) {
        return true;
    }
    else {
        return false;
    }
}

void Square::setType(enum_sqType sqType)
{
    this->sqType = sqType;
}
