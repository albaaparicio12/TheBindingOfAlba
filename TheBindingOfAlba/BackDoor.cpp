#include "BackDoor.h"

BackDoor::BackDoor(float x, float y, Game* game) :
	Door("res/puerta" + to_string(game->currentLevel) + "Abierta.png", x, y, game) {
	isOpen = true;
	isToNextLevel = false;
	if (game->currentLevel - 1 == 0) {
		changeTexture("res/puerta1Abierta.png");
	}
}