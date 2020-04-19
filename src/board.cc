#include "board.h"
#include <iostream>

using namespace std;

Board::Board()
{
	enum_sqType quarterBoard[7][7] =
	{ 
		{ TWS, N  , N  , DWS, N  , N  , N   },
		{ N  , DWS, N  , N  , N  , TLS, N   },
		{ N  , N  , DWS, N  , N  , N  , DLS },
		{ DLS, N  , N  , DWS, N  , N  , N   },
		{ N  , N  , N  , N  , DWS, N  , N   },
		{ N  , TLS, N  , N  , N  , TLS, N   },
		{ N  , N  , DLS, N  , N  , N  , DLS }
	};

	enum_sqType strip[7] = {TWS, N, N, DLS, N, N, N};
	
	/* Top Left */
	for(int i = 0; i < NUM_ROWS/2; i++){
		for(int j = 0; j < NUM_COLS/2; j++){
			board[i][j] = new Square(quarterBoard[i][j], i, j);
		}
	}

	/* Top Right */
	for(int i = 0; i < NUM_ROWS/2; i++){
		for(int j = 0; j < NUM_COLS/2; j++){
			int j2 = NUM_COLS - 1 - j;
			board[i][j2] = new Square(quarterBoard[i][j], i, j2);
		}
	}

	/* Bottom Left */
	for(int i = 0; i < NUM_ROWS/2; i++){
		for(int j = 0; j < NUM_COLS/2; j++){
			int i2 = NUM_ROWS - 1 - i;
			board[i2][j] = new Square(quarterBoard[i][j], i2, j);
		}
	}

	/* Bottom Right */
	for(int i = 0; i < NUM_ROWS/2; i++){
		for(int j = 0; j < NUM_COLS/2; j++){
			int i2 = NUM_ROWS - 1 - i;
			int j2 = NUM_COLS - 1 - j;
			board[i2][j2] = new Square(quarterBoard[i][j], i2, j2);
		}
	}

	for(int j = 0; j < NUM_COLS/2; j++)
		board[NUM_ROWS/2][j] = new Square(strip[j], j, NUM_ROWS/2);

	for(int j = NUM_COLS - 1; j > NUM_COLS/2; j--)
		board[NUM_ROWS/2][j] = new Square(strip[NUM_COLS - 1 - j], j, NUM_ROWS/2);

	for(int j = 0; j < NUM_ROWS/2; j++)
		board[j][NUM_COLS/2] = new Square(strip[j], NUM_COLS/2, j);

	for(int j = NUM_ROWS - 1; j > NUM_ROWS/2; j--)
		board[j][NUM_COLS/2] = new Square(strip[NUM_ROWS - 1 - j], NUM_COLS/2, j);

	board[7][7] = new Square(quarterBoard[1][1], 7, 7);
}

Board::~Board()
{
	for(int i = 0; i < NUM_ROWS; i++){
		for(int j = 0; j < NUM_COLS; j++)
			delete board[i][j];
	}
}

void Board::show()
{
	for(int i = 0; i < NUM_ROWS; i++){
		for(int j = 0; j < NUM_COLS; j++)
			cout << board[i][j]->getType() << " | ";
		cout << endl;
		for(int k = 0; k < NUM_COLS; k++)
			cout << "----";
		cout << endl;
	}
}
