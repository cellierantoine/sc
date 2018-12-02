#include <SFML/Graphics.hpp>
#include "entity.h"
#include "level.h"

#include <iostream>

Player::Player(float x, float y) {
	this->x = x;
	this->y = y;
	speed = 0.05f;
}

void Player::draw(sf::RenderWindow * window, const EntityTextures * textures) {
	const int TILE_SIZE = 32;
	sf::Sprite playerSprite;

	playerSprite.setTexture(textures->player);
	playerSprite.setPosition(x*TILE_SIZE, y*TILE_SIZE);
	window->draw(playerSprite);
}

void Player::move(float mx, float my, sf::Vector2u size, std::vector<Cell> array, float deltaTime, sf::View * view) {
	int posUL = ((int)(x + 0.1 + mx / 32 * speed * deltaTime)*size.y + (int)(y + 0.1 + my / 32 * speed * deltaTime));
	int posUR = ((int)(x + 0.9 + mx / 32 * speed * deltaTime)*size.y + (int)(y + 0.1 + my / 32 * speed * deltaTime));
	int posLL = ((int)(x + 0.1 + mx / 32 * speed * deltaTime)*size.y + (int)(y + 0.9 + my / 32 * speed * deltaTime));
	int posLR = ((int)(x + 0.9 + mx / 32 * speed * deltaTime)*size.y + (int)(y + 0.9 + my / 32 * speed * deltaTime));
	

	if (array[posUL].path && array[posUR].path && array[posLL].path && array[posLR].path) {
		y = y + my/32 * speed;
		x = x + mx/32 * speed;
		view->setCenter(x*32, y*32);
	}
}
