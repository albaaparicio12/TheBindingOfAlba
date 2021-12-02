#include "Explosion.h"
Explosion::Explosion(float x, float y, Game* game) :
	Actor("", x, y, 30, 30, game) {
	time = 5;
}

void Explosion::update() {
	if(time > 0)
		time--;
}