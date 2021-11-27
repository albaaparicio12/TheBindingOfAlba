#pragma once

#include "Enemy.h"

class EnemyChase : public Enemy
{
public:
	EnemyChase(float x, float y, Game* game);
	void update();
	void changeDirection(int x, int y) override;
};
