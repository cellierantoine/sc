#include "device.h"
#include "entity.h"

Farm::Farm() {

}

void Farm::draw(sf::RenderWindow * window, const EntityTextures * textures, int x, int y){
	const int TILE_SIZE = 32;
	sf::Sprite deviceSprite;

	deviceSprite.setTexture(textures->devices[0]);
	deviceSprite.setPosition(x*TILE_SIZE, y*TILE_SIZE);
	window->draw(deviceSprite);
}
