#include <vector>
#include <fstream>
#include <sstream>
#include "tile.h"
#include "square.h"
#include "play.h"
#include "utils.h"

using namespace std;

bool squarePresent(std::vector<Square*> s, Square* target)
{
	auto it = s.end();
	if(target) {
		it = std::find(s.begin(), s.end(), target);
	}
	return(it == s.end() ? false : true);
}

bool tilePresent(std::vector<Tile*> t, Tile* target)
{
	auto it = t.end();
	if(target) {
		it = std::find(t.begin(), t.end(), target);
	}
	return(it == t.end() ? false : true);
}

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

string RawTimeToString(const time_t& t)
{
	ostringstream oss;
	oss << t;
	return oss.str();
}
