#include "BackDoor.h"

BackDoor::BackDoor(float x, float y, Game* game) :
	Door("res/puerta" + to_string(game->currentLevel-1) + "Abierta.png", x, y, game) {
	isOpen = true;
	isToNextLevel = false;
}