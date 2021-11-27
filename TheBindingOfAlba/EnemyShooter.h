#pragma once

#include "Enemy.h"
#include "ProjectileEnemy.h"
class EnemyShooter : public Enemy
{
public:
	EnemyShooter(float x, float y, Game* game);
	void update();
	void changeDirection(int x, int y) override;
	ProjectileEnemy* shoot(int xPlayer, int yPlayer) override;
	int shootCadence = 73;
	int shootTime = 13;
};
