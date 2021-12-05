#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(float x, float y, Game* game) :
	Projectile("res/disparo_enemigo.png", x, y, game) {
}

ProjectileEnemy::ProjectileEnemy(string filename, float x, float y, Game* game) :
	Projectile(filename, x, y, game) {
}

void ProjectileEnemy::update() {
	x = x + vx;
	y = y + vy;
}