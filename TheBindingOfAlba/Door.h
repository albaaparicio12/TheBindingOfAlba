#pragma once
#include "Game.h"
#include "Tile.h"
#include "Audio.h"

class Door : public Tile
{
public:
	Door(float x, float y, Game* game);
	Door(string filename, float x, float y, Game* game);
	bool isOpen;
	bool isToNextLevel;
	void open();
	Audio* audioOpen;
};

