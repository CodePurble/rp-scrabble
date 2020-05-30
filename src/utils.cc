/**
  * @file
  */
#include <vector>
#include <fstream>
#include <sstream>
#include "tile.h"
#include "square.h"
#include "play.h"
#include "utils.h"

using namespace std;

/**
 * Checks whether a Square* is present in a vector<Square*>
 *
 * @param s Vector to search in
 * @param target Search target
 *
 * @return true if found, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool squarePresent(std::vector<Square*> s, Square* target)
{
    auto it = s.end();
    if(target) {
        it = std::find(s.begin(), s.end(), target);
    }
    return(it == s.end() ? false : true);
}

/**
 * Checks whether a Tile* is present in a vector<Tile*>
 *
 * @param t Vector to search in
 * @param target Search target
 *
 * @return true if found, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool tilePresent(std::vector<Tile*> t, Tile* target)
{
    auto it = t.end();
    if(target) {
        it = std::find(t.begin(), t.end(), target);
    }
    return(it == t.end() ? false : true);
}

/**
 * Checks whether a char is present in a string
 *
 * @param str String to search in
 * @param ch Search target
 *
 * @return true if found, false otherwise
 *
 * This function shall not throw exceptions.
 */
bool charPresent(string str, char ch)
{
    auto it = str.end();
    it = std::find(str.begin(), str.end(), ch);
    return(it == str.end() ? false : true);
}

/**
 * Parses a Play in the format <tiles>-<row>-<column>-<direction>
 *
 * @param in String to parse
 *
 * @return Parsed components
 *
 * This function shall not throw exceptions.
 */
std::vector<std::string> parsePlay(std::string in)
{
    vector<string> parse;

    parse.push_back("");

    for(char ch : in) {
        if(ch == '-') {
            parse.push_back("");
        }
        else {
            parse.back().append(1u, ch);
        }
    }

    return parse;
}

/**
 * Log a message to a file
 *
 * @param logFilePath Path to the file to write to
 * @param str Log message
 *
 * @throws std::string containing the error message
 */
void log(string logFilePath, string str)
{
    ofstream logFile(logFilePath, ios::app);

    if(logFile.is_open()) {
        logFile << str + "\n";
    }
    else {
        throw(string("Failed to open log file\n"));
    }

    logFile.close();
}

/**
 * Converts a time_t to a std::string
 *
 * @param t Raw time to convert
 *
 * @return Converted time_t
 *
 * This function shall not throw exceptions.
 */
string RawTimeToString(const time_t& t)
{
    ostringstream oss;
    oss << t;
    return oss.str();
}
