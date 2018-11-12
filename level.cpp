#include <SFML/Graphics.hpp>
#include "level.h"


enum {
	VOID,
	IRON_FLOOR,
	IRON_WALL,
	IRON_DOOR_H
};



void Level::draw(sf::RenderWindow * window, const Textures * textures){
	const int TILE_SIZE = 32;

	sf::Sprite sprite_iron_floor;
	sf::Sprite sprite_iron_wall;
	sf::Sprite sprite_iron_door;
	sprite_iron_floor.setTexture(textures->iron_floor);
	sprite_iron_wall.setTexture(textures->iron_wall);
	sprite_iron_door.setTexture(textures->iron_door_h);

	for (int x = 0; x < level_size.x; x++) {
		for (int y = 0; y < level_size.y; y++) {
			switch (level_tab[x*level_size.y + y]) {
			case IRON_FLOOR:
				sprite_iron_floor.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window->draw(sprite_iron_floor);
				break;
			case IRON_WALL:
				sprite_iron_wall.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window->draw(sprite_iron_wall);
				break;
			case IRON_DOOR_H:
				sprite_iron_door.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				window->draw(sprite_iron_door);
			}	
		}
	}
}

int * Level::getLevelArray(){
	return level_tab;
}

sf::Vector2u Level::getLevelSize() {
	return level_size;
}

Level::Level(const char * level_name) {
	sf::Texture level_tex;
	level_tex.loadFromFile(level_name);
	sf::Vector2u size = level_tex.getSize();
	sf::Image level_img = level_tex.copyToImage();

	level_tab = (int *)malloc(size.x * size.y * sizeof(int));
	level_size = size;

	for (int x = 0; x < size.x; x++) {
		for (int y = 0; y < size.y; y++) {
			sf::Color color = level_img.getPixel(x, y);
			switch (color.toInteger()) {
			case 0x000000FFu : //noir
				level_tab[x*size.y+y] = VOID;
				break;
			case 0xFFFFFFFFu : 
				level_tab[x*size.y + y] = IRON_FLOOR;
				break;
			case 0xFF0000FFu : 
				level_tab[x*size.y + y] = IRON_WALL;
				break;
			case 0xAA0000FFu:
				level_tab[x*size.y + y] = IRON_DOOR_H;
				break;
			}

				
			
		}
	}
	
}

Level::~Level() {
	free(level_tab);
}