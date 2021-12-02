#include "Tile.h"

Tile::Tile(string filename, int x, int y, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	isDestructible = false;
}

Tile::Tile(string filename, float x, float y, int width, int height, Game* game)
	: Actor(filename, x, y, width, height, game) {
	isDestructible = false;
}