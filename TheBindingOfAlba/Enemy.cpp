#include "Enemy.h"

Enemy::Enemy(string filename, float x, float y, int width, int height, Game* game) 
	: Actor(filename, x, y, width, height, game) {
}

void Enemy::draw() {
	if (invulnerableTime == 0) {
		animation->draw(x, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x, y);
		}
	}
}

void Enemy::impacted() {
	if (invulnerableTime <= 0) {
		lifes--;
		invulnerableTime = 40;
		if (lifes <= 0) {
			if (state != States::DYING) 
				state = States::DYING;			
		}
			
	}	
}