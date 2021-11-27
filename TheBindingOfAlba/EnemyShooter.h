#pragma once

#include "Enemy.h"

class EnemyShooter : public Enemy
{
public:
	EnemyShooter(float x, float y, Game* game);
	void update();
	void changeDirection(int x, int y) override;
};
