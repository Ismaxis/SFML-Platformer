#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include"Player.h"
#include"Map.h"
#include"Camera.h"
#include "Level.h"

//Variables types rules:
//Sizes - unsigned int
//Draw position - int
//Physical position - float

int main()
{
	//Map
	//Map map("Maps/map5.csv", "Textures/mapSheet64.png");

	//// Sizes
	//const unsigned int tileSize = map.getCageSize(); //Game
	//const sf::Vector2u gridTileSize = map.getGridSize(); //Game
	//const sf::Vector2u mapPixelSize{ gridTileSize.x * tileSize, gridTileSize.y * tileSize }; //Game

	const sf::Vector2u winPixelSize{ 1920, 1080 };
	//const sf::Vector2u winTileSize = { winPixelSize.x / tileSize, winPixelSize.y / tileSize + 1u }; //Game

	// Window init
	sf::RenderWindow window(sf::VideoMode(winPixelSize.x - 1u, winPixelSize.y - 1u), "Game", sf::Style::Default);
	window.setFramerateLimit(144);
    //window.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
	window.setPosition(sf::Vector2i(0, 0));
	
	//// Player
	//Player player("Textures/Player.png"); //Game 
	//player.setPos(sf::Vector2f(10 * tileSize, 20 * tileSize)); //Game

	//// Variables
	//sf::Clock clock; //Game 
	//int direction{ 0 }; //Game|Player
	//int grabDirection{ 0 }; //Game|Player

	//// Offsets params
	//sf::Vector2i offset; //Game|Cam
	//Camera cam(winPixelSize, mapPixelSize); //Game

	Layout* curLayout = new Level("Maps/map5.csv", "Textures/mapSheet64.png", "Textures/Player.png", winPixelSize);

	// Window loop
	while (window.isOpen())
	{
		/*const int time = clock.restart().asMilliseconds();
		bool isJump = false;*/
		
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

			//if (event.type == sf::Event::KeyPressed)
			//{
			//	// X movement
			//	if (event.key.code == sf::Keyboard::D)
			//	{
			//		direction = 1;
			//	}
			//	else if (event.key.code == sf::Keyboard::A)
			//	{
			//		direction = -1;
			//	}

			//	// Jump 
			//	if (event.key.code == sf::Keyboard::Space && (player.isOnGround() || player.isOnStairs()))
			//	{
			//		isJump = true;
			//	}

			//	// Stairs grab
			//	if (player.isStairsAvailable())
			//	{
			//		if (event.key.code == sf::Keyboard::W)
			//		{
			//			grabDirection = -1;
			//		}
			//		else if (event.key.code == sf::Keyboard::S)
			//		{
			//			grabDirection = 1;
			//		}
			//	}
			//}
			//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			//{
			//	direction = 0;
			//}
			//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			//{
			//	grabDirection = 0;
			//}

		}

		curLayout->update(events);

		window.draw(curLayout->getSprite());
		window.display();

		// Update
		/*player.move(direction);
		
		if (player.isStairsAvailable() && grabDirection != 0)
		{
			player.grab(grabDirection);
		}

		if (isJump)
		{
			player.jump();
		}
		
		player.update(map, time);*/



		//// Offsets
		//offset = cam.calculateOffsets(player.getPos(), player.getVel());

		//// Clear
		//window.clear(sf::Color::White);

		//// Draw
		//// Map draw
		//const sf::Vector2i offsetInCages{ static_cast<int> (offset.x / tileSize), static_cast<int> (offset.y / tileSize) };
		//for (float i = 0; i < winTileSize.y + 1; i++)
		//{
		//	for (float j = 0; j < winTileSize.x + 1; j++)
		//	{
		//		window.draw(map.getSprite(sf::Vector2f(j + offsetInCages.x, i + offsetInCages.y), offset));
		//	}
		//}

		//// Player draw
		//window.draw(player.getSprite(offset));
		//window.display();
	}
}