#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo.png", x, y, 25, 19, game) {
}

Projectile::Projectile(string filename, float x, float y, Game* game) :
	Actor(filename, x, y, 25, 19, game) {
}

void Projectile::update() {
	x = x + vx;
	y = y + vy;
}
