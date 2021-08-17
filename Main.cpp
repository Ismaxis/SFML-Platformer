#include<SFML/Graphics.hpp>
#include<iostream>

#include<ctime>
#include"Player.h"
#include"Map.h"


int main()
{	
	//Map
	Map map("Maps/map3.txt", "Textures/mapSheet32.png");

	// Sizes
	const float tileSize = map.getCageSize();
	const sf::Vector2u gridTileSize = map.getGridSize();
	const sf::Vector2f mapPixelSize{ gridTileSize.x * tileSize, gridTileSize.y * tileSize };
	
	const sf::Vector2f winPixelSize{ float(sf::VideoMode::getDesktopMode().width - 1), float(sf::VideoMode::getDesktopMode().height - 1) };
	const sf::Vector2f winTileSize = { winPixelSize.x/tileSize,  round(winPixelSize.y/tileSize) };
	
	//const sf::Vector2f winPixelSize{ winTileSize.x * tileSize, winTileSize.y * tileSize };
	
	// Window
	sf::RenderWindow window(sf::VideoMode(winPixelSize.x, winPixelSize.y), "Game", sf::Style::None);
	window.setFramerateLimit(144);
	//window.setPosition(sf::Vector2i(350, 150));
	//window.setSize(sf::Vector2u(2 * winPixelSize.x / 3, 2 * winPixelSize.y / 3));
	
	// Player
	Player player("Textures/Player64X128.png");
	player.setPos(sf::Vector2f(200.0f,  mapPixelSize.y / 2.0f));

	// Variables
	sf::Vector2f offset{ 0, 0 };
	sf::Clock clock;
	int direction{ 0 };
	
	// Window loop
	while (window.isOpen())
	{
		const int time = clock.restart().asMilliseconds();

		// Event loop
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::TouchBegan)
			{
				std::cout << std::endl;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				// X movement
				if (event.key.code == sf::Keyboard::D)
				{
					direction = 1;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					direction = -1;
				}

				// Jump 
				if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::W) && player.getStatus())
				{
					player.jump();
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				direction = 0;
			}
		}


		// Update
		player.move(direction);
		player.update(map, time);

		sf::Vector2f playerPos = player.getPos();
		if (playerPos.x > mapPixelSize.x - winPixelSize.x / 2)
		{
			offset.x = mapPixelSize.x - winPixelSize.x;
		}
		else if (playerPos.x > winPixelSize.x / 2)
		{
			offset.x = playerPos.x - winPixelSize.x / 2;
		}
		else
		{
			offset.x = 0;
		}


		// Clear
		window.clear(sf::Color::White);


		// Draw block
		const sf::Vector2f offsetInCages{ offset.x / tileSize, offset.y / tileSize };
		for (float i = 0; i < winTileSize.y; i++)
		{
			for (float j = 0; j < winTileSize.x + 1; j++)
			{
				window.draw(map.getSprite(sf::Vector2u(j + offsetInCages.x, i + offsetInCages.y), offset));
			}
		}

		window.draw(player.getSprite(offset));
		window.display();
	}
}