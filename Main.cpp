#include<SFML/Graphics.hpp>
#include<iostream>

#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include<ctime>
#include"Player.h"
#include"Map.h"

using namespace sf;
using namespace std;


int main()
{	
	// Window
	const Vector2u winSize = {960, 544};
	const int cageSize = 16;
	const Vector2u gridSize = { winSize.x / cageSize, winSize.y / cageSize };
	RenderWindow window(VideoMode(winSize.x, winSize.y), "SFML window", Style::Default);
	window.setFramerateLimit(60);
	
	//Map
	Map map;

	map.setMap("map.txt");
	map.setSheet("Textures/mapSheet.png");

	std::vector<std::vector<sf::Sprite>> mapSprite;

	// Player
	Player player;
	Vector2f curVel = { 0, 0 };
	Vector2i curPos;
	int defVel = 5;
	bool isCollide, prevCollide = false;
	player.init(Vector2i(winSize.x/10, winSize.y/2), "Textures/Player05.png");


	// Window loop
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				// X movement
				if (event.key.code == Keyboard::D)// && !Keyboard::isKeyPressed(Keyboard::A))
				{
					curVel.x = defVel;
				}
				else if (event.key.code == Keyboard::A)// && !Keyboard::isKeyPressed(Keyboard::D))
				{
					curVel.x = -defVel;
				}
				
				// Jump 
				if (event.key.code == Keyboard::Space || event.key.code == Keyboard::W)
				{
					curVel.y = 10;
				}
			}
			else if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
			{
				curVel.x = 0;
			}
		}

		// Clear
		window.clear(Color::White);

		// Colllision check
		curPos = player.getPos();

		isCollide = map.isCollide(curPos);
		if (isCollide) {
			if (!prevCollide)
			{
				curVel.y = 0;
				player.setPos(sf::Vector2i(curPos.x, int(curPos.y / cageSize) * cageSize));
			}
		}
		prevCollide = isCollide;

		// X
		if (curPos.x > winSize.x)
		{
			curVel.x = 0;
			player.setPos(Vector2i(winSize.x, curPos.y));
		}
		else if (curPos.x < 0)
		{
			curVel.x = 0;
			player.setPos(Vector2i(1, curPos.y));
		}
		
		// Y
		if (curPos.y < winSize.y && !isCollide)
		{
			curVel.y -= 1;
		}
		else if (curPos.y > winSize.y)
		{
			player.setPos(Vector2i(curPos.x, winSize.y));
			curVel.y = 0;
		}

		// Update
		player.update(curVel);

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

