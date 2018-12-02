#include <SFML/Graphics.hpp>
#include "level.h"
#include "entity.h"
#include <iostream>



void loadTexture(Textures * textures, EntityTextures * entityTextures) {
	std::string direction[] = { "E", "N", "S", "W", 
								"EN", "ES", "EW", "NS", "NW", "SW",
								"ENS", "ESW", "ENW", "NSW",
								"ENSW"};


	textures->iron_floor.loadFromFile("assets/iron_floor.png");
	textures->iron_door_h.loadFromFile("assets/iron_door_h.png");
	textures->iron_wall.resize(sizeof(direction) / sizeof(direction[0]));
	for (int i = 0; i < sizeof(direction)/sizeof(direction[0]); i++) {
		textures->iron_wall[i].loadFromFile("assets/walls/sc_wall_" + direction[i] + ".png");
	}

	entityTextures->player.loadFromFile("assets/player.png");
}

int main()
{
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(480, 640), "Test"/*, sf::Style::Fullscreen*/);
	window.setKeyRepeatEnabled(false);

	Textures textures;
	EntityTextures entityTextures;

	loadTexture(&textures, &entityTextures);

	Level level("assets/test.png");
	Player player(7, 7);
	sf::View view = window.getDefaultView();
	view.setCenter(7 * 32, 7 * 32);
	window.setView(view);

	while (window.isOpen())
	{
		//Récuperation de la durée d'une frame
		auto deltaTime = clock.getElapsedTime();

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
			player.move(0, -1, level.getLevelSize(), level.getLevelArray(), deltaTime.asSeconds(), &view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			player.move(-1, 0, level.getLevelSize(), level.getLevelArray(), deltaTime.asSeconds(), &view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.move(1, 0, level.getLevelSize(), level.getLevelArray(), deltaTime.asSeconds(), &view);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			player.move(0, 1, level.getLevelSize(), level.getLevelArray(), deltaTime.asSeconds(), &view);
		}
		window.setView(view);

		window.display();

	}

	return 0;
}

