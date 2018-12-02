#include <SFML/Graphics.hpp>
#include "level.h"


enum {
	VOID,
	IRON_FLOOR,
	IRON_DOOR_H
};


void Level::draw(sf::RenderWindow * window, const Textures * textures){
	const int TILE_SIZE = 32;

	sf::Sprite sprite_iron_floor;
	sf::Sprite sprite_iron_door;
	sprite_iron_floor.setTexture(textures->iron_floor);
	sprite_iron_door.setTexture(textures->iron_door_h);

	for (unsigned int x = 0; x < level_size.x; x++) {
		for (unsigned int y = 0; y < level_size.y; y++) {
			switch (level_tab[x*level_size.y + y].sprite) {
			case IRON_FLOOR:
				sprite_iron_floor.setPosition((float)x * TILE_SIZE, (float)y * TILE_SIZE);
				window->draw(sprite_iron_floor);
				break;
			case IRON_DOOR_H:
				sprite_iron_door.setPosition((float)x * TILE_SIZE, (float)y * TILE_SIZE);
				window->draw(sprite_iron_door);
			}	
		}
	}
}

std::vector<Cell> Level::getLevelArray(){
	return level_tab;
}

sf::Vector2u Level::getLevelSize() {
	return level_size;
}

Level::Level(const char * level_name) {
	//link between color and ground sprite
	std::map<unsigned int,std::pair<int, bool>> match_sprite;
	match_sprite[0x000000FFu] = std::make_pair(VOID, false);
	match_sprite[0xFFFFFFFFu] = std::make_pair(IRON_FLOOR, true);
	match_sprite[0xFF0000FFu] = std::make_pair(IRON_DOOR_H, true);


	sf::Texture level_tex;
	level_tex.loadFromFile(level_name);
	sf::Vector2u size = level_tex.getSize();
	sf::Image level_img = level_tex.copyToImage();

	level_tab.resize(size.y * size.x);
	level_size = size;

	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			sf::Color color = level_img.getPixel(x, y);
			level_tab[x*size.y + y].sprite = match_sprite[color.toInteger()].first;
			level_tab[x*size.y + y].path = match_sprite[color.toInteger()].second;
		}
	}
	
}

