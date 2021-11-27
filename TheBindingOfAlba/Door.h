#pragma once
#include "Game.h"
#include "Tile.h"

class Door : public Tile
{
public:
	Door(float x, float y, Game* game);
	Door(string filename, float x, float y, Game* game);
	bool isOpen;
	void open();
};

