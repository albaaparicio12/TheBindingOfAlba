#include "Boss.h"


Boss::Boss(float x, float y, Game* game)
	: Enemy("res/boss.png", x, y, 60, 66, game) {

	vx = 1;

	state = States::IDLE;

	aDying = new Animation("res/boss2.png", width, height,
		600, 66, 4, 10, false, game);
	aMoving = new Animation("res/boss2.png", width, height,
		600, 66, 4, 10, true, game);
	animation = aMoving;

	lifes = 6;
	isBoss = true;
}

void Boss::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	bool endAnimation = animation->update();
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

void Boss::changeDirection(int x, int y) {
	if (this->x > x)
		vx = -2;
	else if (this->x < x)
		vx = 2;
	if (this->y > y)
		vy = -2;
	else if (this->y < y)
		vy = 2;
	if (this->y == y) {
		vy = 0;
	}
	if (this->x == x) {
		vx = 0;
	}
}

ProjectileEnemy* Boss::shoot(int xPlayer, int yPlayer) {
	if (shootTime <= 0) {
		shootTime = shootCadence;
		auto projectile = new ProjectileEnemy(x, y, game);
		if (x - xPlayer > 10)
			projectile->vx = -5;

		else if (x - xPlayer < -10)
			projectile->vx = 5;

		if (y - yPlayer > 10)
			projectile->vy = -5;

		else if (y - yPlayer < -10)
			projectile->vy = 5;

		if (x - xPlayer <= 10 && x - xPlayer >= -10) {
			if (y > yPlayer) {
				projectile->vy = -5;
				projectile->vx = 0;
			}
			else {
				projectile->vy = 5;
				projectile->vx = 0;
			}
		}
		if (y - yPlayer <= 10 && y - yPlayer >= -10) {
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

