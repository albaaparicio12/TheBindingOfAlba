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