#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Game.h"
#include "ProjectileEnemy.h"

class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	virtual void update() = 0;
	void draw() override;
	void impacted(); 
	virtual void changeDirection(int x, int y) = 0;
	virtual ProjectileEnemy* shoot(int xPlayer, int yPlayer) = 0;
	States state = States::IDLE;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation;

	int lifes;
	int invulnerableTime;

	bool isBoss = false;
};
