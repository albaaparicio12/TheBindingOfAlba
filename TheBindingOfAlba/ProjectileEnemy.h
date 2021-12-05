#pragma once
#include "Projectile.h"

class ProjectileEnemy : public Projectile
{
public:
	ProjectileEnemy(float x, float y, Game* game);
	ProjectileEnemy(string filename, float x, float y, Game* game);
	void update();
};

