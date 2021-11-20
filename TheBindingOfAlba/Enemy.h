#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Game.h"
class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update();
	void draw() override;
	void impacted(); 
	void changeDirection(float x, float y);

	States state = States::IDLE;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation;
};
