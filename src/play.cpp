/**
  * @file
  */
#include "tile.h"
#include "square.h"
#include "board.h"
#include "player.h"
#include "play.h"
#include "dict.h"

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
    tilesPlaced = "";
}

/**
  * Play destructor
  */
Play::~Play()
{
    delete playMaker;
}

void Play::log(Logger *logger, std::string logFilePath)
{
    string wordStr = "";
    char logbuf[64];
    for(string s : wordStringsInPlay) {
        wordStr += s;
        wordStr += " + ";
    }
    // Remove trailing " + "
    if(!wordStr.empty()) {
        wordStr.replace(wordStr.end()-3, wordStr.end(), "");
    }
    logger->log("Player: %s\n", playMaker->getName().c_str());
    logger->log("Words in play: %s\n", wordStr.c_str());
    logger->log("%d points\n\n", pointsMade);

    // player,rack,tiles,x,y,dir,words,points,rack
    snprintf(logbuf, IM_ARRAYSIZE(logbuf),
            "%s,%s,%s,%d,%d,%c,%s,%d\n",
            playMaker->getName().c_str(),
            playMaker->getRackStr(true).c_str(),
            tilesPlaced.c_str(),
            row,
            col,
            dir,
            wordStr.c_str(),
            pointsMade
        );
    try {
        logger->fileLog(logFilePath, logbuf);
    }
    catch(string err) {
        BOLD_RED_FG(" " + err);
        BOLD_RED_FG(" You can set the path of the log file in CMakeLists.txt\n");
        BOLD_RED_FG(" Aborting\n");
        exit(1);
    }
}

/**
 * "Pretty print" the Play
 */
void Play::show()
{
    string wordStr = "";
    for(vector<Tile*> word : wordsInPlay) {
        for(Tile* t : word) {
            wordStr += t->getLetter();
        }
        wordStr += " + ";
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
bool Play::checkPlacement(string tileStr, Board* b, int r, int c, char dir)
{
    int max = tileStr.length();
    for(char &c : tileStr) {
        tilesPlaced += toupper(c);
    }
    bool result = false;
    Square* curr;
    this->row = r;
    this->col = c;
    this->dir = dir;

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
vector<vector<Tile*>> Play::getWords(vector<Tile*> tilesInStr, Board* b, int row, int col, char dir)
{
    vector<Tile*> placedTiles;
    Square* currSquare;
    string wordString = "";

    try {
        if(dir == 'h') {
            try {
                currSquare = b->getSquare(row, col);
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

                for(vector<Tile*> tiles : wordsInPlay) {
                    wordString = "";
                    for(Tile *t : tiles) {
                        wordString += t->getLetter();
                    }
                    wordStringsInPlay.push_back(wordString);
                }
            }
            catch(string err) {
                throw;
            }
        }
        else if(dir == 'v') {
            try {
                currSquare = b->getSquare(row, col);
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
                for(vector<Tile*> tiles : wordsInPlay) {
                    wordString = "";
                    for(Tile *t : tiles) {
                        wordString += t->getLetter();
                    }
                    wordStringsInPlay.push_back(wordString);
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

string Play::checkWords(Dict *dictionary)
{
    for(string word : wordStringsInPlay) {
        if(!dictionary->search(word)) {
            return word;
        }
    }
    return "";
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
    int wordPoints = 0;

    /*
     * enum enum_sqType {N, DWS, TWS, DLS, TLS};
     */
    for(vector<Tile*> word : words) {
        wordPoints = 0;
        multiplier = 1;
        for(Tile* t : word) {
            switch(t->getSquare()->getType()) {
            case N:
                wordPoints += t->getPoints();
                break;
            case DLS:
                if(tilePresent(tileStrVec, t)) {
                    wordPoints += 2*(t->getPoints());
                }
                else {
                    t->show();
                    wordPoints += t->getPoints();
                }
                break;
            case TLS:
                if(tilePresent(tileStrVec, t)) {
                    wordPoints += 3*(t->getPoints());
                }
                else {
                    wordPoints += t->getPoints();
                }
                break;
            case TWS:
                wordPoints += t->getPoints();
                if(tilePresent(tileStrVec, t)) {
                    multiplier = 3;
                }
                break;
            case DWS:
                wordPoints += t->getPoints();
                if(tilePresent(tileStrVec, t)) {
                    multiplier = 2;
                }
                break;
            }
        }
        wordPoints *= multiplier;
        pointsMade += wordPoints;
    }
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
    wordStringsInPlay.clear();
    tilesPlaced = "";
    row = 0;
    col = 0;
    dir = ' ';
}
