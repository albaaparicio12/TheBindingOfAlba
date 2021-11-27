#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game) 
	: Actor(filename, x, y, width, height, game) {
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
}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != States::DYING) {
		state = States::DYING;
	}
}

void Enemy::changeDirection(int x, int y) {
}