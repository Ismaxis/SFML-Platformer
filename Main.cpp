#include<SFML/Graphics.hpp>
#include<iostream>

#include<ctime>
#include"Player.h"
#include"Map.h"


int main()
{	
	// Window
	const sf::Vector2i winSize = { 960, 544 };
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "SFML window", sf::Style::Default);
	window.setFramerateLimit(60);

	// Player
	Player player("Textures/Player32X64.png");
	player.setPos(sf::Vector2f(winSize.x / 10, winSize.y / 2));
	sf::Vector2f curVel;
	sf::Vector2f curPos;
	sf::Vector2f nextPos;

	//Map
	Map map("Maps/map2.txt", "Maps/mapSheet.png", player.getSize());
	std::vector<std::vector<sf::Sprite>> mapSprite;

	const int cageSize = map.getCageSize();
	const sf::Vector2i gridSize = { winSize.x / cageSize, winSize.y / cageSize };

	const sf::Vector2f defVel = { 5.0f, 15.0f };
	float maxVel = cageSize;
	sf::Vector2<sf::Vector2<bool>> isCollide = { {false, false}, {false, false} };

	// Window loop
	while (window.isOpen())
	{
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
					curVel.x = defVel.x;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					curVel.x = -defVel.x;
				}
				
				// Jump 
				if ((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::W) && curVel.y == 0)
				{
					curVel.y = defVel.y;
				}
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				curVel.x = 0;
			}
		}
		
		// Max velocity check
		if (abs(curVel.x) > maxVel)
		{
			if (curVel.x > 0)
			{
				curVel.x = maxVel;
			}
			else if (curVel.x < 0)
			{
				curVel.x = -maxVel;
			}
		}
		if (abs(curVel.y) > maxVel)
		{
			if (curVel.y > 0)
			{
				curVel.y = maxVel;
			}
			else if (curVel.y < 0)
			{
				curVel.y = -maxVel;
			}
		}

		player.setVel(curVel);

		// Colllision check
		// Window collide
		curPos = player.getPos();
		// X
		if (curPos.x > winSize.x)
		{
			curVel.x = 0;
			player.setPos(sf::Vector2f(winSize.x - 1, curPos.y));
		}
		else if (curPos.x < 0)
		{
			curVel.x = 0;
			player.setPos(sf::Vector2f(1, curPos.y));
		}
		// Y
		if (curPos.y < winSize.y && !isCollide.y.x)
		{
			curVel.y -= 1;
		}
		else if (curPos.y > winSize.y)
		{
			player.setPos(sf::Vector2f(curPos.x, winSize.y));
			curVel.y = 0;
		}
		
		// Map collide
		curPos = player.getPos();
		player.update();
		nextPos = player.getPos();

		isCollide = map.isCollide(curPos, nextPos);

		// Y bottom
		if (isCollide.y.x) 
		{	
			player.setPos(sf::Vector2f(nextPos.x, int(nextPos.y / cageSize) * cageSize));
			curVel.y = 0;
		
		}
		// Y top
		if (isCollide.y.y)
		{
			player.setPos(sf::Vector2f(nextPos.x, nextPos.y + curVel.y));
			curVel.y = 0;
		}
		// X left
		if (isCollide.x.x)
		{
			player.setPos(sf::Vector2f(int(nextPos.x / cageSize) * cageSize + player.getSize().x / 2, nextPos.y));
		}
		// X right
		if (isCollide.x.y)
		{
			player.setPos(sf::Vector2f(int(nextPos.x / cageSize) * cageSize, nextPos.y));
		}

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

