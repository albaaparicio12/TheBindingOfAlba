#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h" 
#include "Tile.h" 
#include "Space.h" 
#include "EnemyChase.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer l�neas / String
#include <list>


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);

	int newEnemyTime = 0;
	int killedEnemies = 0;

	Player* player;
	Background* background;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;

	Actor* backgroundPoints;
	Text* textPoints;
	int points;

	Audio* audioBackground;

	void loadMap(string name);
	void loadMapObject(char character, int x, int y);
	int mapWidth;
	list<Tile*> tiles;


	Space* space;
};
