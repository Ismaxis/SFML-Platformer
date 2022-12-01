#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
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

std::pair<std::string, std::string> startButtonPaths{"Textures/startButton.png", "Textures/startButtonActive.png"};

std::pair<std::string, std::string> exitButtonPaths{"Textures/exitButton.png", "Textures/exitButtonActive.png"};
std::string pauseLabelPath{"Textures/pause.png"};
std::string emptyPath{"Textures/empty.png"};

int main()
{
	std::string ip;
	std::getline(std::ifstream("config.csv"), ip);
	std::cout << ip;

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
			curLayout = new Level(mapPath, mapSheetPath, playerTexturePath, winPixelSize, ip);
			continue;
		}
		if(updateCode == EXIT_TO_MENU)
		{
			delete curLayout;
			curLayout = new Menu(winPixelSize);
			continue;
		}

		//auto start = std::chrono::steady_clock::now();

		window.clear(sf::Color(255,255,255));
		std::queue<sf::Sprite> sprites = curLayout->getSprites();
		while(!sprites.empty())
		{
			window.draw(sprites.front());
			sprites.pop();
		}
		window.display();

		//auto end = std::chrono::steady_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n";
	}
}