/**
  * @file
  */
#include <fstream>
#include <sstream>
#include <string>
#include "dict.h"
#include "utils.h"

using namespace std;

/**
 * Dictionary constructor.
 * Reads dictionary text file into list of words for searching
 */
Dict::Dict(std::string dictFilePath)
{
    string line;
    ifstream infile(dictFilePath);
    if(infile) {
        while(getline(infile, line)) {
            if(line[0] != '#') {
                wordList.push_back(line);
            }
        }
    }
}

Dict::~Dict()
{
}

/**
 * Check whether a word exists in the wordlist
 *
 * @param word Word to search in the dictionary
 *
 * @return true if found, false if not
 *
 * This function shall not throw exceptions.
 */
bool Dict::search(string word)
{
    auto it = wordList.end();
    it = std::find(wordList.begin(), wordList.end(), word);
    return(it == wordList.end() ? false : true);
}

