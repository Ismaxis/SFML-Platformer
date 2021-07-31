#include<SFML/Graphics.hpp>
#include<iostream>

#include<ctime>
#include"Player.h"
#include"Map.h"


int main()
{	
	//Map
	Map map("Maps/map2.txt", "Maps/mapSheet.png");
	std::vector<std::vector<sf::Sprite>> mapSprite;
	sf::Vector2u gridSize = map.getGridSize();

	// Window
	const sf::Vector2u winSize = { gridSize.x * map.getCageSize(), gridSize.y * map.getCageSize() };
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Platformer", sf::Style::None);
	window.setFramerateLimit(60);

	// Player
	Player player("Textures/Player32X64.png");
	player.setPos(sf::Vector2f(winSize.x / 10, winSize.y / 2));


	sf::Clock clock;
	int lastDir = 0;
	// Window loop
	while (window.isOpen())
	{
		float time = clock.restart().asMilliseconds();

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
					player.Jump();
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				lastDir = 0;
			}
		}


		// Update
		player.Move(lastDir);
		player.update(map, time);


		// Clear
		window.clear(sf::Color::White);
	

		// Draw block
		mapSprite = map.getSprites();

		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{ 
				window.draw(mapSprite[i][j]);
			}
		}

		window.draw(player.getSprite());
		window.display();
	}
	system("exit");
}

