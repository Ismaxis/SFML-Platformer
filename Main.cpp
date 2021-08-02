#include<SFML/Graphics.hpp>
#include<iostream>

#include<ctime>
#include"Player.h"
#include"Map.h"


int main()
{	
	//Map
	Map map("Maps/map3.txt", "Maps/mapSheet.png");
	
	sf::Vector2u gridSize = map.getGridSize();
	const sf::Vector2u mapSize{ gridSize.x * map.getCageSize(), gridSize.y * map.getCageSize() };

	// Window
	const sf::Vector2u winSize{ 60 * 16, 34 * 16 };
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Game", sf::Style::None);
	window.setFramerateLimit(60);

	// Player
	Player player("Textures/Player32X64.png");
	player.setPos(sf::Vector2f(96.0f, (9 * mapSize.y )/ 11.0f));

	// Variables
	sf::Vector2f offset {0, 0};
	sf::Clock clock;
	int lastDir{ 0 };
	
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

			if (event.type == sf::Event::KeyPressed)
			{
				// X movement
				if (event.key.code == sf::Keyboard::D)
				{
					lastDir = 1;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					lastDir = -1;
				}
				
				// Jump 
				if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::W) && player.getStatus())
				{
					player.jump();
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				lastDir = 0;
			}
		}


		// Update
		player.move(lastDir);
		player.update(map, time);

		sf::Vector2f playerPos = player.getPos();
		if (playerPos.x > 300)
		{
			offset.x = playerPos.x - 300;
		}
		else
		{
			offset.x = 0;
		}
		
		// Clear
		window.clear(sf::Color::White);
	

		// Draw block
		std::vector<std::vector<sf::Sprite>> mapSprite = map.getSprites(offset);

		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{ 
				window.draw(mapSprite[i][j]);
			}
		}

		window.draw(player.getSprite(offset));
		window.display();
	}
	system("exit");
}

