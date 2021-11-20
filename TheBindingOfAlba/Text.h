#pragma once

#include "Game.h"

class Text
{
public:Text(string content, float x, float y, Game* game);
	void draw();
	string content; // texto
	int x, y, width, height;
	Game* game; // referencia al juego
};
