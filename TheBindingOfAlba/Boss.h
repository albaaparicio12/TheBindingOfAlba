#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
public:
	Boss(float x, float y, Game* game);
	void update();
	void changeDirection(int x, int y) override;
	ProjectileEnemy* shoot(int xPlayer, int yPlayer) override;
	int shootCadence = 150;
	int shootTime = 0;
};

