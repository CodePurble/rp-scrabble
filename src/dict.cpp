/**
  * @file
  */
#include <fstream>
#include <sstream>
#include <string>
#include "dict.h"
#include "utils.h"

using namespace std;

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

bool Dict::search(string word)
{
    auto it = wordList.end();
    it = std::find(wordList.begin(), wordList.end(), word);
    return(it == wordList.end() ? false : true);
}

