#include <vector>
#include "tile.h"
#include "square.h"
#include "utils.h"

using namespace std;

bool findSquare(std::vector<Square*> s, Square* target)
{
	auto it = s.end();
	if(target)
		it = std::find(s.begin(), s.end(), target);
	return(it == s.end() ? false : true);
}

bool findTile(std::vector<Tile*> t, Tile* target)
{
	auto it = t.end();
	if(target)
		it = std::find(t.begin(), t.end(), target);
	return(it == t.end() ? false : true);
}

std::vector<std::string> parsePlay(std::string in)
{
	vector<string> parse;

	parse.push_back("");

	for(char ch : in){
		if(ch == '-')
			parse.push_back("");
		else{
			parse.back().append(1u, ch);
		}
	}

	return parse;
}

