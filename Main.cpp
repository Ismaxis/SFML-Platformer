#include <SFML/Graphics.hpp>
#include <iostream>
#include "Layout/Layout.h"
#include "Layout/Level/Level.h"
#include "Layout/Menu/Menu.h"
#include "Layout/updateCodes.h"

//Variables types rules:
//Sizes - unsigned int
//Draw position - int
//Physical position - float

std::string mapPath{"Maps/map5.csv"};
std::string mapSheetPath{"Textures/mapSheet64.png"};
std::string playerTexturePath{"Textures/Player.png"};

int main()
{
	// Window init
	const sf::Vector2u winPixelSize{ 1920, 1080 };
	sf::RenderWindow window(sf::VideoMode(winPixelSize.x - 1u, winPixelSize.y - 1u), "Game", sf::Style::Default);
	window.setFramerateLimit(144);
	window.setPosition(sf::Vector2i(0, 0));
	
	Layout* curLayout = new Menu(winPixelSize);

	// Window loop
	while (window.isOpen())
	{
		// Event loop
		sf::Event event;
		Inputs input;
		std::vector<sf::Event> events;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			events.push_back(event);
		}

		input.events = events;
		input.mousePos = sf::Mouse::getPosition(window);

		int updateCode = curLayout->update(input);

		if(updateCode == START_LEVEL)
		{
			delete curLayout;
			curLayout = new Level(mapPath, mapSheetPath, playerTexturePath, winPixelSize);
		}
		if(updateCode == EXIT_TO_MENU)
		{
			delete curLayout;
			curLayout = new Menu(winPixelSize);
		}

		window.draw(curLayout->getSprite());
		window.display();
	}
}