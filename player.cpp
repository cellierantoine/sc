#include <SFML/Graphics.hpp>
#include "entity.h"
#include "level.h"

#include <iostream>

Player::Player(float x, float y) {
	this->x = x;
	this->y = y;
	speed = 4;
}

void Player::draw(sf::RenderWindow * window, const EntityTextures * textures) {
	const int TILE_SIZE = 32;
	sf::Sprite playerSprite;

	playerSprite.setTexture(textures->player);
	playerSprite.setPosition(x*TILE_SIZE, y*TILE_SIZE);
	window->draw(playerSprite);
}

void Player::move(float mx, float my, sf::Vector2u size, int * array) {
	int posUL = ((int)(x + 0.1 + mx / 32 * speed)*size.y + (int)(y + 0.1 + my / 32 * speed));
	int posUR = ((int)(x + 0.9 + mx / 32 * speed)*size.y + (int)(y + 0.1 + my / 32 * speed));
	int posLL = ((int)(x + 0.1 + mx / 32 * speed)*size.y + (int)(y + 0.9 + my / 32 * speed));
	int posLR = ((int)(x + 0.9 + mx / 32 * speed)*size.y + (int)(y + 0.9 + my / 32 * speed));
	



	if (array[posUL] != 0 && array[posUR] != 0 && array[posLL] != 0 && array[posLR] != 0) {
		y = y + my/32 * speed;
		x = x + mx/32 * speed;
	}
}
