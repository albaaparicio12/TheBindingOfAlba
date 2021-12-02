#include "Door.h"

Door::Door(float x, float y, Game* game) :
	Tile("res/puerta"+to_string(game->currentLevel)+"Cerrada.png", x, y, 49, 35, game) {
	isOpen = false;
	isToNextLevel = true;

	audioOpen = new Audio("res/open_door.wav", false);
}

Door::Door(string filename, float x, float y, Game* game) :
	Tile(filename, x, y, 49, 35, game) {
	isOpen = false;
	isToNextLevel = true;

	audioOpen = new Audio("res/open_door.wav", false);
}

void Door::open() {
	audioOpen->play();
	isOpen = true;
	changeTexture("res/puerta" + to_string(game->currentLevel) + "Abierta.png");
}