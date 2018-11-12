#include <SFML/Graphics.hpp>
#include "level.h"
#include "entity.h"

void loadTexture(Textures * textures, EntityTextures * entityTextures) {
	textures->iron_floor.loadFromFile("assets/png/iron_floor.png");
	textures->iron_wall.loadFromFile("assets/png/iron_wall.png");
	textures->iron_door_h.loadFromFile("assets/png/iron_door_h.png");

	entityTextures->player.loadFromFile("assets/png/player.png");
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(480, 640), "Test");
	window.setKeyRepeatEnabled(false);

	Textures textures;
	EntityTextures entityTextures;

	loadTexture(&textures, &entityTextures);

	Level level("assets/png/test.png");
	Player player(7, 7);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		//Affichage du décor
		level.draw(&window, &textures);
		player.draw(&window, &entityTextures);

		//Deplacement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			player.move(0, -1, level.getLevelSize(), level.getLevelArray());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			player.move(-1, 0, level.getLevelSize(), level.getLevelArray());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.move(1, 0, level.getLevelSize(), level.getLevelArray());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.move(0, 1, level.getLevelSize(), level.getLevelArray());
		}


		window.display();

	}

	return 0;
}

