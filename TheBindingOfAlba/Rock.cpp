#include "Rock.h"

Rock::Rock(float x, float y, Game* game) :
	Tile(randomImage(), x, y, 42, 42, game) {
}

Rock::Rock(string filename, float x, float y, Game* game) :
	Tile(filename, x, y, 42, 42, game) {

}

string Rock::randomImage() {
	level = 1;
	int r = (rand() % 3)+1;
	return "res/rocks/level" + to_string(level) + "/roca" + to_string(r) + ".png";
}

