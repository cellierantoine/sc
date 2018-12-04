#ifndef DEVICE_H
#define DEVICE_H

#include <SFML/Graphics.hpp>

struct EntityTextures;

class Device {
public:
	virtual void draw(sf::RenderWindow * window, const EntityTextures * textures, int x, int y) = 0;
};

class Farm : public Device {
public :
	Farm();
	void draw(sf::RenderWindow * window, const EntityTextures * textures, int x, int y) override;
};

#endif