#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game) 
	: Actor(filename, x, y, width, height, game) {
}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != States::DYING) {
		state = States::DYING;
	}
}