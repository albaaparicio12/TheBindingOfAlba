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
	int shootCadence = 20;
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
	void getShoot(int n);

	int bombs = 0;
	void addBomb();
	Bomb* putBomb();
	int bombCadence = 30;
	int bombTime = 0;
	bool hasKey;

	void addLife();
};
