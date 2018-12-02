#include <SFML/Graphics.hpp>
#include "level.h"
#include <iostream>


enum {
	VOID,
	IRON_FLOOR,
	IRON_DOOR_H,
	SC_WALL_E,
	SC_WALL_N,
	SC_WALL_S,
	SC_WALL_W,
	SC_WALL_EN,
	SC_WALL_ES,
	SC_WALL_EW,
	SC_WALL_NS,
	SC_WALL_NW,
	SC_WALL_SW,
	SC_WALL_ENS,
	SC_WALL_ENW,
	SC_WALL_ESW,
	SC_WALL_NSW,
	SC_WALL_ENSW
};


void Level::draw(sf::RenderWindow * window, const Textures * textures, const EntityTextures * entityTextures){
	const int TILE_SIZE = 32;
	sf::Sprite tmpSprite;
	for (unsigned int x = 0; x < level_size.x; x++) {
		for (unsigned int y = 0; y < level_size.y; y++) {
			//Display sprite texture
			int spriteID = level_tab[x*level_size.y + y].sprite;
			if (spriteID == IRON_FLOOR) {
				tmpSprite.setTexture(textures->iron_floor);
			}
			else if (spriteID == IRON_DOOR_H) {
				tmpSprite.setTexture(textures->iron_door_h);
			}
			else if (spriteID >= SC_WALL_E && spriteID <= SC_WALL_ENSW) {
				tmpSprite.setTexture(textures->iron_wall[spriteID - SC_WALL_E]);
			}

			if (spriteID != VOID) {
				tmpSprite.setPosition((float)x * TILE_SIZE, (float)y * TILE_SIZE);
				window->draw(tmpSprite);

				//Display device texture
				if (level_tab[x*level_size.y + y].device) {
					level_tab[x*level_size.y + y].device->draw(window, entityTextures, x, y);
				}
			}
		}
	}
}

const std::vector<Cell> &Level::getLevelArray() const{
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
	//Walls
	for (int i = 0; i < 15; i++) {
		match_sprite[i*0x00010000u + 0xFF0200FFu] = std::make_pair(i + SC_WALL_E, false);
	}


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

	level_tab[8 * size.y + 8].device.reset(new Farm());
	level_tab[8 * size.y + 8].path = false;
}

