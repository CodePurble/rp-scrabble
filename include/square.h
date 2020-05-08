#ifndef SQUARE_H
#define SQUARE_H

class Tile;

enum enum_sqType {N, DWS, TWS, DLS, TLS};

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
