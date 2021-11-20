#include "Animation.h"

Animation::Animation(string filename, float actorWidth, float actorHeight,
	float fileWidth, float fileHeight,
	int updateFrecuence, int totalFrames, bool loop, Game* game)
	: actorHeight(actorHeight), actorWidth(actorWidth), fileHeight(fileHeight),
	fileWidth(fileWidth), updateFrecuence(updateFrecuence), totalFrames(totalFrames),
	game(game), updateTime(0), currentFrame(0), loop(loop) {

	// Cargar textura
	texture = game->getTexture(filename);

	// Calcular lo que mide un fotograma/frame
	frameWidth = fileWidth / totalFrames;
	frameHeigt = fileHeight;

	// Rectangulo de recorte de fotograma
	source.x = 0;
	source.y = 0;
	source.w = frameWidth;
	source.h = frameHeigt;
}

bool Animation::update() {
	updateTime++;
	if (updateTime > updateFrecuence) {
		updateTime = 0;
		// Actualizar el frame
		currentFrame++;
		// Si lleva al ultimo frame vuelve al primero
		if (currentFrame >= totalFrames) {
			currentFrame = 0;
			if (!loop) {
				// No es infinita
				// Indicar que finalizó 
				return true;
			}
		}
	}
	//Actualizar el rectangulo del source (siguiente frame)
	source.x = currentFrame * frameWidth;
	return false; // luego lo cambiamos
}

void Animation::draw(float x, float y) {
	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - actorWidth / 2;
	destination.y = y - actorHeight / 2;
	destination.w = actorWidth;
	destination.h = actorHeight;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);

}
