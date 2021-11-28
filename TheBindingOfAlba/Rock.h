#pragma once
#include "Game.h"
#include "Tile.h"

class Rock : public Tile
{
public:
	Rock(float x, float y, Game* game);
	Rock(string filename, float x, float y, Game* game);
	int level;
	string randomImage();
};

