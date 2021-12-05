#include "Door.h"

Door::Door(float x, float y, Game* game) :
	Tile("res/puerta"+to_string(game->currentLevel+1)+"Cerrada.png", x, y, 49, 35, game) {
	isOpen = false;
	isToNextLevel = true;

	audioOpen = new Audio("res/open_door.wav", false);

	if (game->currentLevel == 0) {
		isOpen = true;
		changeTexture("res/puerta1Abierta.png");
	}
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
	changeTexture("res/puerta" + to_string(game->currentLevel+1) + "Abierta.png");
}