#include "Rock.h"

Rock::Rock(float x, float y,int level, Game* game) :
	Tile(randomImage(level), x, y, 42, 42, game) {
}

string Rock::randomImage(int level) {
	int r = (rand() % 3)+1;
	return "res/rocks/level" + to_string(level) + "/roca" + to_string(r) + ".png";
}

