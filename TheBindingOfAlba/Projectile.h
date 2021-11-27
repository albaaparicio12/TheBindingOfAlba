#pragma once

#include "Actor.h"

class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	Projectile(string filename, float x, float y, Game* game);
	void update();
};
