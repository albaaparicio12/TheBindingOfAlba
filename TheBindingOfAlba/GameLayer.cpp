#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	gamePad = SDL_GameControllerOpen(0);
	init();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();
}

void GameLayer::init() {
	space = new Space(0);
	tiles.clear();
	projectiles.clear();
	projectilesEnemy.clear();
	bombs.clear();
	enemies.clear();
	explosions.clear();
	doors.clear();
	hearts.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	background = new Background("res/mapa"+to_string(game->currentLevel)+".png", WIDTH * 0.5, HEIGHT * 0.5, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH*0.9, HEIGHT*0.55,100,100,game);
	buttonBomb = new Actor("res/boton_bomba.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);
	backgroundLifes = new Actor("res/corazon" + to_string(player->lives) + ".png", WIDTH * 0.1, HEIGHT * 0.05, 76, 22, game);
	backgroundBombs = new Actor("res/bombIcon.png", WIDTH * 0.05, HEIGHT * 0.15, 22, 19, game);
	textBombs = new Text(to_string(player->bombs), WIDTH * 0.1, HEIGHT * 0.15, game);

}

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		 // PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}

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
			Bomb* newBomb = player->putBomb();
			if (newBomb != NULL) {
				space->addDynamicActor(newBomb);
				bombs.push_back(newBomb);
				player->bombs = player->bombs - 1;
				textBombs->content = to_string(player->bombs);
				cout << "Bomb to explode" << endl;
			}
		}
	}

	if (controlContinue) {
		pause = false;
		controlContinue = false;
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

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			// CLICK TAMBIEN TE MUEVE
			controlMoveX = pad->getOrientationX(motionX);
			controlMoveY = pad->getOrientationY(motionY);
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}
		if (buttonBomb->containsPoint(motionX, motionY)) {
			controlBomb = true;
		}
	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
			if (pad->clicked && pad->containsPoint(motionX, motionY)) {
				controlMoveX = pad->getOrientationX(motionX);
				controlMoveY = pad->getOrientationY(motionY);
				// Rango de -20 a 20 es igual que 0
				if (controlMoveX > -20 && controlMoveX < 20) {
					controlMoveX = 0;
				}
				if (controlMoveY > -20 && controlMoveY < 20) {
					controlMoveY = 0;
				}
			}
			else {
				controlMoveX = 0;
				controlMoveY = 0;
				pad->clicked = false;
			}
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}
		if (buttonBomb->containsPoint(motionX, motionY) == false) {
			controlBomb = false;
		}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
			controlMoveY = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}
		if (buttonBomb->containsPoint(motionX, motionY)) {
			controlBomb = false;
		}
	}
}


void GameLayer::update() {
	if (pause) {
		return;
	}
	space->update();
	player->update();

	for (auto const& door : doors) {
		if (player->isOverlap(door) && door->isOpen) {
			if (door->isToNextLevel) {
				nextLevel();
				break;
			}
			else {
				backLevel();
				break;
			}
		}
	}

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
				endGame();
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
	list<Heart*> deleteHearts;

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
					return;
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
			for (auto const& door : doors) {
				if (door->isOverlap(projectile)) {
					bool pInList = std::find(deleteProjectilesEnemy.begin(),
						deleteProjectilesEnemy.end(),
						projectile) != deleteProjectilesEnemy.end();

					if (!pInList) {
						deleteProjectilesEnemy.push_back(projectile);
					}
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
			for (auto const& door : doors) {
				if (door->isOverlap(projectile)) {
					bool pInList = std::find(deleteProjectiles.begin(),
						deleteProjectiles.end(),
						projectile) != deleteProjectiles.end();

					if (!pInList) {
						deleteProjectiles.push_back(projectile);
					}
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
			if (enemy->isBoss) {
				nextLevel();
				return;
			}
			if (generateRandomBomb(enemy->x, enemy->y))
				generateRandomHeart(enemy->x + 10, enemy->y);
			else
				generateRandomHeart(enemy->x, enemy->y);
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
					key = new Key(tile->x, tile->y, game);
					space->addDynamicActor(key);
				}
			}
		}
	}
	bool abrir = false;
	for (auto const& door : doors) {
		if (key != NULL && player->isOverlap(key)) {
			player->hasKey = true;
			abrir = true;
			space->removeDynamicActor(key);
			key = NULL;
		}
		if (abrir && door->isToNextLevel)
			door->open();
	}

	for (auto const& heart : hearts) {
		if (player->isOverlap(heart)) {
			if (player->lives < 6) {
				player->addLife();
				backgroundLifes->changeTexture("res/corazon" + to_string(player->lives) + ".png");
			}
			bool eInList = std::find(deleteHearts.begin(),
				deleteHearts.end(),
				heart) != deleteHearts.end();

			if (!eInList) {
				deleteHearts.push_back(heart);
			}
		}
		
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

		for (auto const& delEx : deleteExplosions) {
			explosions.remove(delEx);
			space->removeStaticActor(delEx);
		}
		deleteExplosions.clear();

		for (auto const& delTile : deleteTiles) {
			tiles.remove(delTile);
			space->removeStaticActor(delTile);
		}
		deleteTiles.clear();

		for (auto const& delHeart : deleteHearts) {
			hearts.remove(delHeart);
			space->removeDynamicActor(delHeart);
		}
		deleteHearts.clear();
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

		for (auto const& heart : hearts) {
			heart->draw();
		}

		for (auto const& door : doors) {
			door->draw();
		}

		if (key != NULL)
			key->draw();

		player->draw();
		for (auto const& enemy : enemies) {
			enemy->draw();
		}

		for (auto const& projectileEnemie : projectilesEnemy) {
			projectileEnemie->draw();
		}

		// HUD
		if (game->input == game->inputMouse) {
			buttonBomb->draw();
			buttonShoot->draw(); 
			pad->draw(); 
		}
		if (pause) {
			message->draw();
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
		case 'J': {
			Enemy* enemy = new Boss(x, y, game);
			enemy->y = enemy->y - enemy->height / 2;
			enemies.push_back(enemy);
			space->addDynamicActor(enemy);
			break;
		}
		case 'D': {
			Door* door = new Door(x, y, game);
			door->y = door->y - door->height / 2;
			doors.push_back(door);
			space->addStaticActor(door);
			break;
		}
		case 'B': {
			Door* door = new BackDoor(x, y, game);
			door->y = door->y - door->height / 2;
			doors.push_back(door);
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
			if (player == NULL) {
				player = new Player(x, y, game);
			}
			space->addDynamicActor(player);
			player->x = x;
			player->y = y;
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
	game->currentLevel = 0;
	player = NULL;
	init();
}

bool GameLayer::generateRandomBomb(int x, int y) {
	int r = (rand() % 2) + 1;
	if (r == 1) {
		Bomb* bomb = new Bomb("res/bombReco.png", x, y, false, game);
		bombs.push_back(bomb);
		space->addDynamicActor(bomb);
		return true;
	}return false;
}

bool GameLayer::generateRandomHeart(int x, int y) {
	int r = (rand() % 3) + 1;
	if (r == 1) {
		Heart* heart = new Heart(x, y, game);
		hearts.push_back(heart);
		space->addDynamicActor(heart);
		return true;
	}return false;
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
		game->currentLevel = 0;
		message = new Actor("res/menu_final.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		endGame();
	}
	init();
}

void GameLayer::backLevel() {
	game->currentLevel--;
	if (game->currentLevel < 0) {
		game->currentLevel = 0;
	}
	init();
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	// SDL_CONTROLLER_BUTTON_A
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA <<  endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (buttonA) {
		controlShoot = true;
	}
	else {
		controlShoot = false;
	}

	if (stickY > 4000) {
		controlMoveY = 1;
	}
	else if (stickY < -4000) {
		controlMoveY = -1;
	}
}
