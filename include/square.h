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
		Square* up;
		Square* down;


	public:
		Square(enum_sqType st, int r, int c);
		~Square(){}

		int getRow();
		int getCol();
		int getType();
		Square* getLeft();
		Square* getRight();
		Square* getUp();
		Square* getDown();
		Tile* getTile();

		void setLeft(Square* l);
		void setRight(Square* r);
		void setUp(Square* u);
		void setDown(Square* d);
		void setTile(Tile* t);

		bool isEmpty();
		void show();
};

#endif
