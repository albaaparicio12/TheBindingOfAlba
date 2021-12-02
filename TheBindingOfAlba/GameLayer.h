#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "ProjectileEnemy.h"
#include "Text.h"
#include "Audio.h" 
#include "Tile.h" 
#include "Space.h" 
#include "EnemyChase.h"
#include "EnemyShooter.h"
#include "Tile.h"
#include "Door.h"
#include "Rock.h"
#include "Explosion.h"
#include "KeyRock.h"
#include "Key.h"
#include "BackDoor.h"
#include "Heart.h"

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
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
	bool controlBomb = false;

	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<ProjectileEnemy*> projectilesEnemy;
	list<Tile*> tiles;

	Actor* backgroundLifes;
	Actor* backgroundBombs;
	Text* textBombs;
	Audio* audioBackground;

	void loadMap(string name);
	void loadMapObject(char character, int x, int y);
	int mapWidth;

	Space* space;

	void endGame();
	bool generateRandomBomb(int x, int y);
	void createExplosions(int x, int y);
	list<Bomb*> bombs;
	list<Explosion*> explosions;

	Key* key;
	list<Door*> doors;
	
	void nextLevel();
	void backLevel();

	bool generateRandomHeart(int x, int y);
	list<Heart*> hearts;
};
