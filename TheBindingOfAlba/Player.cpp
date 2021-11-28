#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 38, 35, game) {

	audioShoot = new Audio("res/efecto_disparo.wav", false);

	aIdleRight = new Animation("res/idle_right.png", width, height,
		38, 35, 1, 1, true, game);
	aIdleLeft = new Animation("res/idle_left.png", width, height,
		38, 35, 6, 1, true, game);
	aRunningLeft = new Animation("res/walk_left.png", width, height,
		114, 35, 6, 3, true, game);
	aRunningRight = new Animation("res/walk_right.png", width, height,
		114, 35, 6, 3, true, game);
	aIdleUp = new Animation("res/idle_up.png", width, height,
		38, 35, 6, 1, true, game);
	aIdleDown = new Animation("res/idle_down.png", width, height,
		38, 35, 6, 1, true, game);
	aRunningUp = new Animation("res/walk_up.png", width, height,
		114, 35, 6, 3, true, game);
	aRunningDown = new Animation("res/walk_down.png", width, height,
		114, 35, 6, 3, true, game);

	animation = aIdleRight;

}

void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}
	bool hasAnimationEnded = animation->update();
	if (hasAnimationEnded) {
		if (state == States::SHOOTING) {
			state = States::IDLE;
		}
	}

	if (shootTime > 0) {
		shootTime--;
	}

	//Update orientation
	if (vx > 0) {
		orientation = Orientation::RIGHT;
	}
	else if (vx < 0) {
		orientation = Orientation::LEFT;
	}
	if (vy > 0) {
		orientation = Orientation::DOWN;
	}
	else if (vy < 0) {
		orientation = Orientation::UP;
	}
	//Update state
	if (state != States::SHOOTING) {

		if (vx != 0 || vy!= 0) {
			state = States::MOVING;
		}
		else {
			state = States::IDLE;
		}
	}

	//Update animation
	switch (state)
	{
		case (States::MOVING):
			if (orientation == Orientation::RIGHT)
				animation = aRunningRight;
			else if (orientation == Orientation::LEFT)
				animation = aRunningLeft;
			else if (orientation == Orientation::UP)
				animation = aRunningUp;
			else
				animation = aRunningDown;
			break;
		default:
			if (orientation == Orientation::RIGHT)
				animation = aIdleRight;
			else if (orientation == Orientation::LEFT)
				animation = aIdleLeft;
			else if (orientation == Orientation::UP)
				animation = aIdleUp;
			else
				animation = aIdleDown;
			break;
		}

}

void Player::moveX(float axis) {
	vx = axis * 3;
}

void Player::moveY(float axis) {
	vy = axis * 3;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		audioShoot->play();
		shootTime = shootCadence;
		auto projectile = new Projectile(x, y, game);
		if (orientation == Orientation::LEFT) {
			projectile->vx = -6;
		}
		else if (orientation == Orientation::RIGHT) {
			projectile->vx = 6;
		}
		else if (orientation == Orientation::UP) {
			projectile->vy = -6;
		}
		else if (orientation == Orientation::DOWN) {
			projectile->vy = 6;
		}
		return projectile;
	}
	else {
		return NULL;
	}

}

void Player::draw() {
	if (invulnerableTime == 0) {
		animation->draw(x, y);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animation->draw(x, y);
		}
	}
}

void Player::getShoot() {
	if (invulnerableTime <= 0) {
		if (lives > 0) {
			lives--;
			invulnerableTime = 50;
		}
	}
}

void Player::addBomb() {
	bombs++;
}