#include "Bomb.h"
Bomb::Bomb(float x, float y,bool ex, Game* game) :
	Actor("res/bomb.png", x, y, 35, 38, game) {
	toExplode = ex;
	explodeTime = 10;
}

Bomb::Bomb(string filename, float x, float y,bool ex, Game* game) :
	Actor(filename, x, y, 35, 38, game) {
	toExplode = ex;
	explodeTime = 10;
}

void Bomb::explode() {

}

void Bomb::update() {
	if (explodeTime == 0) {
		explodeTime = 10;
	}
}
