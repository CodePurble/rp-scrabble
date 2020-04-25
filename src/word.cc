#include "word.h"
#include "rack.h"
#include "tile.h"

using namespace std;

Word::Word(string w, Rack* r)
{
	for(char ch : w){
		Tile* target = r->getTile(ch);
		if(target){
			word.push_back(target);
			wordScore += target->getPoints();
		}
	}
}
