#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

struct Textures {
	sf::Texture iron_floor;
	sf::Texture iron_wall;
	sf::Texture iron_door_h;
};


class Level {
private:
	int * level_tab;
	sf::Vector2u level_size;
public:
	Level(const char* level_name);
	~Level();
	void draw(sf::RenderWindow * window, const Textures * textures);

	int * getLevelArray();
	sf::Vector2u getLevelSize();
};


#endif