#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	init();
}

void GameLayer::init() {
	space = new Space(0);
	tiles.clear();

	background = new Background("res/mapa1.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	backgroundLifes = new Actor("res/corazon6.png", WIDTH * 0.1, HEIGHT * 0.05, 76, 22, game);
	backgroundBombs = new Actor("res/bombIcon.png", WIDTH * 0.05, HEIGHT * 0.15, 22, 19, game);
	textBombs = new Text("0", WIDTH * 0.1, HEIGHT * 0.15, game);

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	projectiles.clear();
	projectilesEnemy.clear();
	bombs.clear();
	enemies.clear();
	explosions.clear();
	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		keysToControls(event);
	}
	//procesar controles
	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
			cout << "Proyectile" << endl;
		}

	}

	if (controlBomb) {
		if (player->bombs > 0) {
			Bomb* newBomb = new Bomb(player->x, player->y, true, game);
			space->addDynamicActor(newBomb);
			bombs.push_back(newBomb);
			player->bombs = player->bombs - 1;
			textBombs->content = to_string(player->bombs);
			cout << "Bomb to explode" << endl;
		}
	}
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}

}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		game->loopActive = false;
		return;
	}
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		case SDLK_b: // bomba
			controlBomb = true;
			break;
		}
	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;

		case SDLK_b: // bomba
			controlBomb = false;
			break;
		}

	}
}

void GameLayer::update() {
	space->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update();
		enemy->changeDirection(player->x, player->y);
		ProjectileEnemy* newProjectile = enemy->shoot(player->x, player->y);
		if (newProjectile != NULL) {
			projectilesEnemy.push_back(newProjectile);
		}
	}

	for (auto const& projectile : projectiles) {
		projectile->update();
	}

	for (auto const& projectile : projectilesEnemy) {
		projectile->update();
	}

	for (auto const& bomb : bombs) {
		bomb->update();
	}

	for (auto const& ex : explosions) {
		ex->update();
	}

	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			player->getShoot();
			if (player->lives <= 0) {
				init();
				return;
			}
			backgroundLifes->changeTexture("res/corazon" + to_string(player->lives) + ".png");
		}
	}
	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<ProjectileEnemy*> deleteProjectilesEnemy;
	list<Bomb*> deleteBombs;
	list<Explosion*> deleteExplosions;
	list<Tile*> deleteTiles;

	for (auto const& tile : tiles) {
		for (auto const& projectile : projectilesEnemy) {
			if (projectile->isOverlap(player)) {
				bool pInList = std::find(deleteProjectilesEnemy.begin(),
					deleteProjectilesEnemy.end(),
					projectile) != deleteProjectilesEnemy.end();

				if (!pInList) {
					deleteProjectilesEnemy.push_back(projectile);
				}
				player->getShoot();
				if (player->lives == 0) {
					endGame();
				}
				backgroundLifes->changeTexture("res/corazon" + to_string(player->lives) + ".png");
			}
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectilesEnemy.begin(),
					deleteProjectilesEnemy.end(),
					projectile) != deleteProjectilesEnemy.end();

				if (!pInList) {
					deleteProjectilesEnemy.push_back(projectile);
				}
			}
		}
	}

	for (auto const& tile : tiles) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
				enemy->impacted();
			}
		}
	}

	for (auto const& enemy : enemies) {
		if (enemy->state == States::DEAD) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
			generateRandomBomb(enemy->x, enemy->y);
		}

	}

	for (auto const& bomb : bombs) {
		if (bomb->isOverlap(player) && bomb->toExplode == false) {
			bool eInList = std::find(deleteBombs.begin(),
				deleteBombs.end(),
				bomb) != deleteBombs.end();

			if (!eInList) {
				deleteBombs.push_back(bomb);
			}
			player->addBomb();
			textBombs->content = to_string(player->bombs);
		}
	}

	for (auto const& bomb : bombs) {
		if (bomb->state == StatesBomb::DESTROYED) {
			bool eInList = std::find(deleteBombs.begin(),
				deleteBombs.end(),
				bomb) != deleteBombs.end();

			if (!eInList) {
				deleteBombs.push_back(bomb);
			}
			createExplosions(bomb->x, bomb->y);
		}
	}

	for (auto const& ex : explosions) {
		if (ex->time == 0) {
			bool eInList = std::find(deleteExplosions.begin(),
				deleteExplosions.end(),
				ex) != deleteExplosions.end();

			if (!eInList) {
				deleteExplosions.push_back(ex);
			}
		}
		for (auto const& tile : tiles) {
			if (ex->isOverlap(tile) && tile->isDestructible) {
				bool eInList = std::find(deleteTiles.begin(),
					deleteTiles.end(),
					tile) != deleteTiles.end();

				if (!eInList) {
					deleteTiles.push_back(tile);
				}

				if (tile->hasKey) {
					key = new Key(tile->x,tile->y,game);
					space->addDynamicActor(key);
				}
			}
		}
	}

	if (key != NULL && player->isOverlap(key)) {
		player->hasKey = true;
		door->open();
		space->removeDynamicActor(key);
		key = NULL;
	}

	if (player->isOverlap(door) && door->isOpen) {
		nextLevel();
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		killedEnemies++;
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
	}
	deleteProjectiles.clear();

	for (auto const& delProjectile : deleteProjectilesEnemy) {
		projectilesEnemy.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
	}
	deleteProjectilesEnemy.clear();

	for (auto const& delBomb : deleteBombs) {
		bombs.remove(delBomb);
		space->removeDynamicActor(delBomb);
	}
	deleteBombs.clear();

	for (auto const& delEx: deleteExplosions) {
		explosions.remove(delEx);
		space->removeStaticActor(delEx);
	}
	deleteExplosions.clear();

	for (auto const& delTile : deleteTiles) {
		tiles.remove(delTile);
		space->removeStaticActor(delTile);
	}
	deleteTiles.clear();
}

void GameLayer::draw() {
	background->draw();
	backgroundLifes->draw();
	backgroundBombs->draw();
	textBombs->draw();
	for (auto const& tile : tiles) {
		tile->draw();
	}

	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	for (auto const& bomb : bombs) {
		bomb->draw();
	}
	door->draw();
	if(key != NULL)
		key->draw();
	player->draw();
	for (auto const& enemy : enemies) {
		enemy->draw();
	}

	for (auto const& projectileEnemie : projectilesEnemy) {
		projectileEnemie->draw();
	}

	SDL_RenderPresent(game->renderer);
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, int x, int y)
{
	switch (character) {
	case 'E': {
		Enemy* enemy = new EnemyChase(x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'S': {
		Enemy* enemy = new EnemyShooter(x, y, game);
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'D': {
		door = new Door(x, y, game);
		door->y = door->y - door->height / 2;
		space->addStaticActor(door);
		break;
	}
	case 'R': {
		Tile* rock = new Rock(x, y, game->currentLevel, game);
		rock->y = rock->y - rock->height / 2;
		tiles.push_back(rock);
		space->addStaticActor(rock);
		break;
	}
	case 'K': {
		Tile* rock = new KeyRock(x, y, game->currentLevel, game);
		rock->y = rock->y - rock->height / 2;
		tiles.push_back(rock);
		space->addStaticActor(rock);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::endGame() {
	init();
	return;
}

void GameLayer::generateRandomBomb(int x, int y) {
	int r = (rand() % 2) + 1;
	if (r == 1) {
		Bomb* bomb = new Bomb("res/bombReco.png", x, y, false, game);
		bombs.push_back(bomb);
		space->addDynamicActor(bomb);
	}
}

void GameLayer::createExplosions(int x, int y) {
	Explosion* exup = new Explosion(x, y+5, game);
	Explosion* exdown = new Explosion(x, y-5, game);
	Explosion* exleft = new Explosion(x-5, y, game);
	Explosion* exright = new Explosion(x+5, y, game);

	explosions.push_back(exup);
	space->addStaticActor(exup);
	explosions.push_back(exdown);
	space->addStaticActor(exdown);
	explosions.push_back(exleft);
	space->addStaticActor(exleft);
	explosions.push_back(exright);
	space->addStaticActor(exright);
}

void GameLayer::nextLevel() {
	game->currentLevel++;
	if (game->currentLevel > game->finalLevel) {
		game->currentLevel = 1;
	}
	init();
}