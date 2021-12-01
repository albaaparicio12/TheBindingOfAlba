#include "KeyRock.h"

KeyRock::KeyRock(float x, float y, int level, Game* game) :
	Rock(x, y, level, game) {
	hasKey = true;
}