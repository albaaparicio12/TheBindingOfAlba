#include "Bomb.h"
Bomb::Bomb(float x, float y,bool ex, Game* game) :
	Actor("res/bomb.png", x, y, 35, 38, game) {
	toExplode = ex;

	aIdle = new Animation("res/bombReco.png", 35, 38,
		35, 38, 1, 1, true, game);
	aBeforeExplode = new Animation("res/bombReco.png", 35, 38,
		35, 38, 40, 1, false, game);
	aExploding = new Animation("res/bomb_exploding.png", 38, 36,
		266, 36, 4, 7, false, game);
	
	if (toExplode) {
		animation = aBeforeExplode;
		state = StatesBomb::EXPLODING;
	}
	else {
		animation = aIdle;
		state = StatesBomb::IDLE;
	}
}

Bomb::Bomb(string filename, float x, float y, bool ex, Game* game) :
	Actor(filename, x, y, 35, 38, game) {
	toExplode = ex;
	aIdle = new Animation("res/bombReco.png", 35, 38,
		35, 38, 1, 1, true, game);
	aBeforeExplode = new Animation("res/bombReco.png", 35, 38,
		35, 38, 40, 1, false, game);
	aExploding = new Animation("res/bomb_exploding.png", 38, 36,
		267, 36, 7,7, false, game);

	if (toExplode) {
		animation = aBeforeExplode;
		state = StatesBomb::EXPLODING;
	}
	else {
		animation = aIdle;
		state = StatesBomb::IDLE;
	}
}

void Bomb::update() {
	bool hasAnimationEnded = animation->update();
	if (hasAnimationEnded) {
		if (animation == aBeforeExplode) {
			animation = aExploding;
		}
		else {
			state = StatesBomb::DESTROYED;
		}
	}
}

void Bomb::draw() {
	animation->draw(x, y);
}
