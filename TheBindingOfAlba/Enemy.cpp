#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/spider.png", x, y, 32, 32, game) {

	vx = 1;

	state = States::IDLE;

	aDying = new Animation("res/spider_die.png", width, height,
		128, 32, 6, 4, false, game);
	aMoving = new Animation("res/spider_move.png", width, height,
		128, 32, 6, 4, true, game);
	animation = aMoving;

}

void Enemy::update() {
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

	if (state != States::DYING) {
		vx = -1;
	}


}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != States::DYING) {
		state = States::DYING;
	}
}

void Enemy::changeDirection(float x, float y) {
	if (x < 0)
		vx = 1;
	else if (x > 0)
		vx = -1;
	if (y < 0)
		vy = 1;
	else if (y > 0)
		vy = -1;
}