#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

struct Textures {
	sf::Texture iron_floor;
	sf::Texture iron_door_h;
	std::vector<sf::Texture> iron_wall;
};

struct Cell {
	int path;
	int sprite;
};


class Level {
private:
	std::vector<Cell> level_tab;
	sf::Vector2u level_size;
public:
	Level(const char* level_name);
	void draw(sf::RenderWindow * window, const Textures * textures);

	std::vector<Cell> getLevelArray();
	sf::Vector2u getLevelSize();
};


#endif