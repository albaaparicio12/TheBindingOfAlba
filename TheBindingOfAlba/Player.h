#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Audio.h"
#include "Animation.h" 
#include <list>
#include "Bomb.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	int shootCadence = 30;
	int shootTime = 0;
	Audio* audioShoot;
	void draw() override;
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;
	Animation* aIdleUp;
	Animation* aIdleDown;
	Animation* aRunningUp;
	Animation* aRunningDown;
	Animation* animation;
	
	Orientation orientation = Orientation::RIGHT;
	States state = States::IDLE;

	int lives = 6;
	int invulnerableTime = 0;
	void getShoot();

	int bombs = 0;
	void addBomb();

	bool hasKey;
};
