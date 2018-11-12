#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "level.h"

struct EntityTextures {
	sf::Texture player;
};

class Player {
private:
	sf::Texture playerTex;
public:
	float x;
	float y;
	float speed;

	Player(float x, float y);
	void draw(sf::RenderWindow * window, const EntityTextures * textures);

	void move(float mx, float my, sf::Vector2u size, int * array);

};

#endif
