#ifndef RACK_H
#define RACK_H
#include <array>
#include <vector>

class Tile;

class Rack {
	private:
		std::array<Tile*, 7> rack;

	public:
		Rack();
		~Rack(){};

		void fill(std::vector<Tile*> t);
		void show();
};

#endif
