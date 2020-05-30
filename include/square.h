/**
  * @file
  */
#ifndef SQUARE_H
#define SQUARE_H

class Tile;

/**
 * Type of square
 */
enum enum_sqType {
    /** Normal */
    N  ,
    /** Double Word Score */
    DWS,
    /** Triple Word Score */
    TWS,
    /** Double Letter Score */
    DLS,
    /** Triple Letter Score */
    TLS
};

/**
 * Implements a single square on the Scrabble board
 *
 * Squares can be one of 5 types and can either be empty, or occupied by a Tile
 */
class Square {
private:
    enum_sqType sqType;
    Tile* tileInSquare;
    int row;
    int col;
    Square* left;
    Square* right;
    Square* above;
    Square* below;


public:
    Square(enum_sqType st, int r, int c);
    ~Square() {}

    int getRow();
    int getCol();
    int getType();
    Square* getLeft();
    Square* getRight();
    Square* getAbove();
    Square* getBelow();
    Tile* getTile();

    void setLeft(Square* l);
    void setRight(Square* r);
    void setAbove(Square* u);
    void setBelow(Square* d);
    void setTile(Tile* t);

    bool isEmpty();
    bool checkNeighboursH();
    bool checkNeighboursV();
    void show();
};

#endif
