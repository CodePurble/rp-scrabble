/**
  * @file
  */
#ifndef DICT_H
#define DICT_H
#include <vector>
#include <string>

/**
 * Basic dictionary (maybe I need to take help from gperf some time)
 */
class Dict {
private:
    std::vector<std::string> wordList;

public:
    Dict(std::string dictFilePath);
    ~Dict();
    bool search(std::string word);
};

#endif
