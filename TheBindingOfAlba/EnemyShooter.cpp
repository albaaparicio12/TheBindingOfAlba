#include "EnemyShooter.h"

EnemyShooter::EnemyShooter(float x, float y, Game* game)
	: Enemy("res/gusano_idle.png", x, y, 32, 32, game) {

	vx = 0;

	state = States::IDLE;

	aMoving = new Animation("res/gusano.png", width, height,
		330, 32, 6, 10, true, game);
	aDying = new Animation("res/gusano.png", width, height,
		128, 32, 6, 4, false, game);
	animation = aMoving;

}

void EnemyShooter::update() {
	bool endAnimation = animation->update();
	shootTime--;
	if (endAnimation) {
		if (state == States::DYING) {
			state = States::DEAD;
		}
	}
	if (state == States::IDLE) {
		animation = aMoving;
	}
	if (state == States::DYING) {
		animation = aDying;
	}
}

void EnemyShooter::changeDirection(int x, int y) {
}

ProjectileEnemy* EnemyShooter::shoot(int xPlayer, int yPlayer) {
	if (shootTime <= 0) {
		shootTime = shootCadence;
		auto projectile = new ProjectileEnemy(x, y, game);
		if (x - xPlayer > 10)
			projectile->vx = -5;

		else if (x - xPlayer < -10)
			projectile->vx = 5;

		if (y -yPlayer > 10)
			projectile->vy = -5;

		else if (y - yPlayer < -10)
			projectile->vy = 5;

		if (x - xPlayer <= 10 && x - xPlayer >= -10)  {
			if (y > yPlayer) {
				projectile->vy = -5;
				projectile->vx = 0;
			}
			else {
				projectile->vy = 5;
				projectile->vx = 0;
			}
		}		
		if (y - yPlayer <= 10 && y - yPlayer >= -10)  {
			if (x < xPlayer) {
				projectile->vy = 0;
				projectile->vx = 5;
			}
			else {
				projectile->vy = 0;
				projectile->vx = -5;
			}
		}
		return projectile;
	}
	else {
		return NULL;
	}
}