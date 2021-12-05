#pragma once
#include "Actor.h"
#include "Animation.h"
#include "Audio.h"

class Bomb : public Actor
{
public:
	Bomb(float x, float y,bool toExplode, Game* game);
	Bomb(string filename, float x, float y,bool toExplode, Game* game);
	bool toExplode;
	void update();
	void draw() override;

	Animation* animation;
	Animation* aIdle;
	Animation* aBeforeExplode;
	Animation* aExploding;

	StatesBomb state = StatesBomb::IDLE;

	Audio* audioBomb;
};

