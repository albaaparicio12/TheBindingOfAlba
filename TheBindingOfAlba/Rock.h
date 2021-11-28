#pragma once
#include "Game.h"
#include "Tile.h"

class Rock : public Tile
{
public:
	Rock(float x, float y,int level, Game* game);
	string randomImage(int level);
};

