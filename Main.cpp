#include<SFML/Graphics.hpp>
#include<iostream>

#include<ctime>
#include"Player.h"
#include"Map.h"

//Variables types rules:
//Sizes - unsigned int
//Draw position - int
//Physical position - float

int main()
{
	//Map
	Map map("Maps/map5.csv", "Textures/mapSheet.png");

	// Sizes
	const unsigned int tileSize = map.getCageSize();
	const sf::Vector2u gridTileSize = map.getGridSize();
	const sf::Vector2u mapPixelSize{ gridTileSize.x * tileSize, gridTileSize.y * tileSize };

	//const sf::Vector2u winPixelSize{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
	const sf::Vector2u winPixelSize{ 1920, 1080 };
	const sf::Vector2u winTileSize = { winPixelSize.x / tileSize, winPixelSize.y / tileSize + 1u };

	// Window init
	sf::RenderWindow window(sf::VideoMode(winPixelSize.x - 1u, winPixelSize.y - 1u), "Game", sf::Style::Default);
	window.setFramerateLimit(144);
    //window.setSize(sf::Vector2u( sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	window.setPosition(sf::Vector2i(0, 0));
	
	// Player
	Player player("Textures/Player.png");
	player.setPos(sf::Vector2f(10 * tileSize, 20 * tileSize));

	// Variables
	sf::Clock clock;
	int direction{ 0 };
	int grabDirection{ 0 };

	// Offsets params
	sf::Vector2i offset{ 0, 0 };
	float camAcceleration{ 0 };
	float camVelocity{ 0 };
	
	// Window loop
	while (window.isOpen())
	{
		const int time = clock.restart().asMilliseconds();
		bool isJump = false;
		
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
					direction = -1;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					direction = 1;
				}

				// Jump 
				if (event.key.code == sf::Keyboard::Space && (player.isOnGround() || player.isOnStairs()))
				{
					isJump = true;
				}

				// Stairs grab
				if (player.isStairsAvailable())
				{
					if (event.key.code == sf::Keyboard::W)
					{
						grabDirection = 1;
					}
					else if (event.key.code == sf::Keyboard::S)
					{
						grabDirection = -1;
					}
				}
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				direction = 0;
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				grabDirection = 0;
			}

		}

		// Update
		player.move(direction);
		
		if (player.isStairsAvailable() && grabDirection != 0)
		{
			player.grab(grabDirection);
		}

		if (isJump)
		{
			player.jump();
		}
		
		player.update(map, time);






		// Offsets
		sf::Vector2i playerPos = player.getPos();
		sf::Vector2f playerVel = player.getVel();



		// X offset
		camAcceleration = 0;

		if (offset.x < playerPos.x - winPixelSize.x * 0.8)
		{
			offset.x = playerPos.x - winPixelSize.x * 0.8;
		}
		if (offset.x > abs(playerPos.x - winPixelSize.x * 0.15))
		{
			offset.x = playerPos.x - winPixelSize.x * 0.15;
		}
		if (offset.x <= playerPos.x - winPixelSize.x * 0.49 && offset.x >= playerPos.x - winPixelSize.x * 0.51)
		{
			camAcceleration = 0;
			camVelocity = 0;
		}
		if (offset.x < playerPos.x - winPixelSize.x * 0.5 && playerVel.x == 0)
		{
			camAcceleration = (playerPos.x - winPixelSize.x * 0.5)/9000.0;
		}
		if (offset.x > abs(playerPos.x - winPixelSize.x * 0.5) && playerVel.x == 0)
		{
			camAcceleration = -(playerPos.x - winPixelSize.x * 0.5)/9000.0;
		}

		camVelocity += camAcceleration;
		offset.x += camVelocity;

		if(offset.x < 0)
		{
			camAcceleration = 0;
			camVelocity = 0;
			offset.x = 0;
		}
		if(offset.x > mapPixelSize.x - winPixelSize.x)
		{
			camAcceleration = 0;
			camVelocity = 0;
			offset.x = mapPixelSize.x - winPixelSize.x;
		}

		// Y offset
		if (playerPos.y > mapPixelSize.y - winPixelSize.y / 2u)
		{
			offset.y = mapPixelSize.y - winPixelSize.y;
		}
		else if (playerPos.y > winPixelSize.y / 2u)
		{
			offset.y = playerPos.y - winPixelSize.y / 2u;
		}
		else
		{
			offset.y = 0;
		}





		// Clear
		window.clear(sf::Color::White);

		// Draw
		// Map draw
		const sf::Vector2i offsetInCages{ static_cast<int> (offset.x / tileSize), static_cast<int> (offset.y / tileSize) };
		for (float i = 0; i < winTileSize.y + 1; i++)
		{
			for (float j = 0; j < winTileSize.x + 1; j++)
			{
				window.draw(map.getSprite(sf::Vector2f(j + offsetInCages.x, i + offsetInCages.y), offset));
			}
		}

		// Player draw
		if (player.isOnGround() || player.isOnStairs())
		{
			window.draw(player.dbgSprite(offset));
		}
		window.draw(player.getSprite(offset));
		window.display();
	}
}