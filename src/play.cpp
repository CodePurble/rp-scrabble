/**
  * @file
  */
#include "tile.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "play.h"

using namespace std;

/**
  * Construct a Play
  *
  * @param p Pointer to the Player who is making the Play
  *
  * This function shall note throw exceptions
  */
Play::Play(Player* p)
{
    pointsMade = 0;
    playMaker = p;
    playStr = "";
}

/**
  * Play destructor
  */
Play::~Play()
{
    delete playMaker;
}

/**
 * "Pretty print" the Play
 */
void Play::show()
{
    string wordStr = "";
    for(vector<Tile*> word : wordsInPlay) {
        for(Tile* t : word) {
            wordStr.append(t->getLetterStr());
        }
        wordStr.append(" + ");
    }
    if(!wordStr.empty()) {
        wordStr.replace(wordStr.end()-3, wordStr.end(), "");
    }

    BOLD_WHITE_FG(" Words in play: " + wordStr + "\n");
    BOLD_WHITE_FG(" " + to_string(pointsMade) + " points\n");
}


/**
 * Set the maker of the Play
 *
 * @param p Pointer to a Player object
 *
 * This function shall not throw exceptions.
 */
void Play::setPlayer(Player* p)
{
    playMaker = p;
}

/**
 * Validates whether a requested play is possible or not. Rejection restores the game's condition
 * as it was before the play was made.
 *
 * Algorithm-
 *  1. Start from first placed Tile
 *  2. Check whether the Tile has any neighbours that were placed before the current Tile (ie.
 *  check if the play connects with a previously placed word)
 *  3. If so, play is valid, return true, otherwise, move to next Tile
 *  4. If all placed Tiles are exhausted, return false
 *
 * @param tileStr String of letters that represent the Tiles to be placed
 * @param b Pointer to the Board where the tiles are to be placed
 * @param r Row where the first Tile goes
 * @param c Column where first tile goes
 * @param dir Direction of placement
 *
 * @return true if valid, false otherwise
 *
 * @throws std::string containing the error message
 *
 * @warning Cannot be used to validate the first play
 */
bool Play::validate(string tileStr, Board* b, int r, int c, char dir)
{
    int max = tileStr.length();
    bool result = false;
    Square* curr;

    if(dir == 'h') {
        int currCol = c;
        for(int i = 0; i < max; i++) {
            try {
                curr = b->getSquare(r, currCol);
                Square* currLeft = curr->getLeft();
                Square* currRight = curr->getRight();
                Square* currAbove = curr->getAbove();
                Square* currBelow = curr->getBelow();

                result =
                    ( currLeft && !currLeft->isEmpty() )
                    || ( currRight && !currRight->isEmpty() )
                    || ( currAbove && !currAbove->isEmpty() )
                    || ( currBelow && !currBelow->isEmpty() );

                if(result) {
                    playStr = tileStr;
                    break;
                }
                else {
                    currCol++;
                }
            }
            catch(string err) {
                throw;
            }
        }
    }
    else if(dir == 'v') {
        int currRow = r;
        try {
            for(int i = 0; i < max; i++) {
                curr = b->getSquare(currRow, c);
                Square* currLeft = curr->getLeft();
                Square* currRight = curr->getRight();
                Square* currAbove = curr->getAbove();
                Square* currBelow = curr->getBelow();

                result =
                    ( currLeft && !currLeft->isEmpty() )
                    || ( currRight && !currRight->isEmpty() )
                    || ( currAbove && !currAbove->isEmpty() )
                    || ( currBelow && !currBelow->isEmpty() );

                if(result) {
                    playStr = tileStr;
                    break;
                }
                else {
                    currRow++;
                }
            }
        }
        catch(string err) {
            throw;
        }
    }
    else {
        throw(string("Invalid direction\n"));
    }

    return result;
}

/**
 * Get all new words that were made as a result of successful play
 *
 * @param tilesInStr Vector of Tiles that were placed
 * @param b Pointer to the Board where the Tiles were placed
 * @param r Row where the first Tile goes
 * @param c Column where first tile goes
 * @param dir Direction of placement
 *
 * @return A 2D vector of Tiles containing all the words made as vectors of
 * Tiles
 *
 * @throws std::string containing the error message
 */
vector<vector<Tile*>> Play::getWords(vector<Tile*> tilesInStr, Board* b, int r, int c, char dir)
{
    vector<Tile*> placedTiles;
    int currRow = r;
    int currCol = c;
    Square* currSquare;

    try {
        if(dir == 'h') {
            try {
                currSquare = b->getSquare(currRow, currCol);
                while(currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty()) {
                    currSquare = currSquare->getLeft();
                }

                while(currSquare && !currSquare->isEmpty()) {
                    placedTiles.push_back(currSquare->getTile());
                    currSquare = currSquare->getRight();
                }
                wordsInPlay.push_back(placedTiles);

                for(Tile* t : tilesInStr) {
                    currSquare = t->getSquare();
                    if(( currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty() )
                            || ( currSquare && currSquare->getBelow() && !currSquare->getBelow()->isEmpty() )) {
                        wordsInPlay.push_back(getConnectedWord(t, 'v'));
                    }
                }
            }
            catch(string err) {
                throw;
            }
        }
        else if(dir == 'v') {
            try {
                currSquare = b->getSquare(currRow, currCol);
                while(currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty()) {
                    if(currSquare) {
                        currSquare = currSquare->getAbove();
                    }
                }

                while(currSquare && !currSquare->isEmpty()) {
                    placedTiles.push_back(currSquare->getTile());
                    currSquare = currSquare->getBelow();
                }
                wordsInPlay.push_back(placedTiles);

                for(Tile* t : tilesInStr) {
                    currSquare = t->getSquare();
                    if(( currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty() )
                            || ( currSquare && currSquare->getRight() && !currSquare->getRight()->isEmpty() )) {
                        wordsInPlay.push_back(getConnectedWord(t, 'h'));
                    }
                }
            }
            catch(string err) {
                throw;
            }
        }

    }
    catch(string err) {
        throw;
    }

    return wordsInPlay;
}

/**
 * Get the word that a Tile is part of
 *
 * @param t Tile in question
 * @param searchDir Direction of search
 *
 * @return Vector of Tiles that make up the found "word"
 *
 * @throws std::string containing the error message
 */
vector<Tile*> Play::getConnectedWord(Tile* t, char searchDir)
{
    Square* currSquare;
    vector<Tile*> connectedWord;

    if(searchDir == 'h') {
        currSquare = t->getSquare();
        while(currSquare && currSquare->getLeft() && !currSquare->getLeft()->isEmpty()) {
            currSquare = currSquare->getLeft();
        }

        while(currSquare && !currSquare->isEmpty()) {
            connectedWord.push_back(currSquare->getTile());
            currSquare = currSquare->getRight();
        }
    }
    else if(searchDir == 'v') {
        currSquare = t->getSquare();
        while(currSquare && currSquare->getAbove() && !currSquare->getAbove()->isEmpty()) {
            currSquare = currSquare->getAbove();
        }

        while(currSquare && !currSquare->isEmpty()) {
            connectedWord.push_back(currSquare->getTile());
            currSquare = currSquare->getBelow();
        }
    }
    else {
        throw(string("Invalid direction\n"));
    }

    return connectedWord;
}

/**
 * Calculate the points made when the play was made
 *
 * @param words The words to consider for calculation
 * @param tileStrVec Tiles that were placed in the Play
 *
 * This function shall not throw exceptions.
 */
void Play::calculatePoints(vector<vector<Tile*>> words, vector<Tile*> tileStrVec)
{
    int multiplier = 1;

    /*
     * enum enum_sqType {N, DWS, TWS, DLS, TLS};
     */
    for(vector<Tile*> word : words) {
        for(Tile* t : word) {
            switch(t->getSquare()->getType()) {
            case N:
                pointsMade += t->getPoints();
                break;
            case DLS:
                if(tilePresent(tileStrVec, t)) {
                    pointsMade += 2*(t->getPoints());
                }
                else {
                    t->show();
                    pointsMade += t->getPoints();
                }
                break;
            case TLS:
                if(tilePresent(tileStrVec, t)) {
                    pointsMade += 3*(t->getPoints());
                }
                else {
                    pointsMade += t->getPoints();
                }
                break;
            case TWS:
                pointsMade += t->getPoints();
                if(tilePresent(tileStrVec, t)) {
                    multiplier *= 3;
                }
                break;
            case DWS:
                pointsMade += t->getPoints();
                if(tilePresent(tileStrVec, t)) {
                    multiplier *= 2;
                }
                break;
            }
        }
    }
    pointsMade *= multiplier;
}

/**
 * Getter for pointsMade data member
 *
 * @return pointsMade
 *
 * This function shall not throw exceptions.
 */
int Play::getPointsMade()
{
    return pointsMade;
}

/**
 * Ask whether the play should be confirmed or not
 *
 * @return true if confirmed, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool Play::confirmPlay()
{
    char ch;
    PALE_GREEN_FG(" Confirm the play? (y/n) ");
    cin >> ch;

    switch(ch) {
    case 'y':
        return true;
        break;
    case 'n':
        return false;
        break;
    default:
        return false;
        break;
    }
}

/**
 * Reset the Play to initial conditions
 *
 * This function shall not throw exceptions.
 */
void Play::reset()
{
    pointsMade = 0;
    wordsInPlay.clear();
    playStr = "";
}
