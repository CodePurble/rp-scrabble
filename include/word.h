#ifndef WORD_H
#define WORD_H
#include <string>
#include <vector>

class Tile;
class Rack;

class Word {
	private:
		std::vector<Tile*> word;
		int wordScore;

	public:
		Word(std::string w, Rack* r);
		~Word(){};

};

#endif
