#include "rack.h"
#include "tile.h"
#include <iostream>
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
			t.pop_back();
		}
		i++;
	}
}

void Rack::show()
{
	for(Tile* t : rack){
		if(t)	
			cout << t->getLetter();
	}
	cout << endl;
}
