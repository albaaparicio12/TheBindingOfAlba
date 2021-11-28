#pragma once
#include "Actor.h"

class Bomb : public Actor
{
public:
	Bomb(float x, float y,bool toExplode, Game* game);
	Bomb(string filename, float x, float y,bool toExplode, Game* game);
	bool toExplode;
	void explode();
	int explodeTime;
	void update();
};

