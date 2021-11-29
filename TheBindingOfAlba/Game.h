#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map> 

// Valores generales
#define WIDTH 572
#define HEIGHT 416

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void loop();
	void scale();
	bool scaledToMax = false;
	float scaleLower = 1;
	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache


	TTF_Font* font;

	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* gameLayer;

	int currentLevel = 1;
	int finalLevel = 3;
};

enum class States {
	IDLE,
	MOVING,
	DYING,
	DEAD,
	SHOOTING
};

enum class Orientation {
	RIGHT,
	LEFT,
	UP,
	DOWN
};

enum class StatesBomb {
	IDLE,
	EXPLODING,
	DESTROYED
};