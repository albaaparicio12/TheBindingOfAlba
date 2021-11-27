#include "Door.h"

Door::Door(float x, float y, Game* game) :
	Tile("res/puerta1Cerrada.png", x, y, 49, 35, game) {
	isOpen = false;
}

Door::Door(string filename, float x, float y, Game* game) :
	Tile(filename, x, y, 49, 35, game) {
	isOpen = false;
}

void Door::open() {
	isOpen = true;
	changeTexture("res/puerta1Abierta.png");
}