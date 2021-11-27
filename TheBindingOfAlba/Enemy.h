#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Game.h"
class Enemy : public Actor
{
public:
	Enemy(string filename, float x, float y, int width, int height, Game* game);
	void update();
	void draw() override;
	void impacted(); 
	void changeDirection(int x, int y);

	States state = States::IDLE;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation;
};
