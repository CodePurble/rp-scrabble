#include <iostream>
#include "rack.h"
#include "tile.h"
#include "utils.h"

using namespace std;

Rack::Rack()
{
	rack.fill(nullptr);
}

void Rack::fill(vector<Tile*> t)
{
	int i = 0;
	while(!t.empty() && i < rack.size()){
		if(!rack[i]){
			rack[i] = t.back();
			rack[i]->setLoc(1);
			t.pop_back();
		}
		i++;
	}
}

void Rack::show()
{
	int rackSize = rack.size();

	for(int i = 0; i < rackSize; i++){
		if(i == 0)
			BOLD_WHITE("   " + to_string(i) + "  ");
		else
			BOLD_WHITE(" " + to_string(i) + "  ");
	}
	cout << "\n";

	cout << " ";
	for(int i = 0; i < rackSize; i++)
		BOLD_BROWN("+---");

	BOLD_BROWN("+");
	cout << "\n";
	BOLD_BROWN(" | ");

	for(Tile* t : rack){
		if(t){
			BOLD_WHITE(t->getLetterStr());
			BOLD_BROWN(" | ");
			}
		else{
			BOLD_BROWN("  | ");
		}
	}
	cout << "\n" << " ";
	for(int i = 0; i < rackSize; i++)
		BOLD_BROWN("+---");

	BOLD_BROWN("+");
	cout << "\n";
}

Tile* Rack::getTile(int index)
{
	Tile* t = nullptr;
	if(index > -1 && index < 7){
		t = rack[index];
		rack[index] = nullptr;
	}
	return(t);
}
