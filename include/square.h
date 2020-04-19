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
		
		Square* getLeft();
		Square* getRight();
		Square* getUp();
		Square* getDown();
		int getRow();
		int getCol();
		int getType();
		void show();
};

#endif
