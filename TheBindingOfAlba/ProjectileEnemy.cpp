#include "ProjectileEnemy.h"

ProjectileEnemy::ProjectileEnemy(float x, float y, Game* game) :
	Projectile("res/disparo_enemigo.png", x, y, game) {
	vx = -9;
}