#include "EnemyChase.h"

EnemyChase::EnemyChase(float x, float y, Game* game)
	: Enemy("res/spider.png", x, y, 32, 32, game) {

	vx = 1;

	state = States::IDLE;

	aDying = new Animation("res/spider_die.png", width, height,
		128, 32, 6, 4, false, game);
	aMoving = new Animation("res/spider_move.png", width, height,
		128, 32, 6, 4, true, game);
	animation = aMoving;

}

void EnemyChase::update() {
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