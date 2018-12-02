#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "device.h"

struct Textures {
	sf::Texture iron_floor;
	sf::Texture iron_door_h;
	std::vector<sf::Texture> iron_wall;
};

struct Cell {
	int path;
	int sprite;
	std::unique_ptr<Device> device;
};


class Level {
private:
	std::vector<Cell> level_tab;
	sf::Vector2u level_size;
public:
	Level(const char* level_name);
	void draw(sf::RenderWindow * window, const Textures * textures, const EntityTextures * entityTextures);

	const std::vector<Cell> &getLevelArray() const;
	sf::Vector2u getLevelSize();
};


#endif