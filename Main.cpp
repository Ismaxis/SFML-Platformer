#include<SFML/Graphics.hpp>
#include<iostream>
#include"Player.h"
#include "Layout/Layout.h"
#include "Layout/Level/Level.h"

//Variables types rules:
//Sizes - unsigned int
//Draw position - int
//Physical position - float

int main()
{
	// Window init
	const sf::Vector2u winPixelSize{ 1920, 1080 };
	sf::RenderWindow window(sf::VideoMode(winPixelSize.x - 1u, winPixelSize.y - 1u), "Game", sf::Style::Default);
	window.setFramerateLimit(144);
	window.setPosition(sf::Vector2i(0, 0));

	Layout* curLayout = new Level("Maps/map5.csv", "Textures/mapSheet64.png", "Textures/Player.png", winPixelSize);

	// Window loop
	while (window.isOpen())
	{
		// Event loop
		sf::Event event;
		std::vector<sf::Event> events;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			events.push_back(event);
		}

		curLayout->update(events);

		window.draw(curLayout->getSprite());
		window.display();
	}
}