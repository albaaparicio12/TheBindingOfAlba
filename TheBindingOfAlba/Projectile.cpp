#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo.png", x, y, 25, 19, game) {
	vx = 9;
}

void Projectile::update() {
}
