#include<SFML/Graphics.hpp>
#include<iostream>

#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include<filesystem>
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
	Map map1;

	map1.setMap("map.txt");
	map1.setSheet("Textures/mapSheet.png");

	std::vector<std::vector<sf::Sprite>> mapSprite;

	// Player
	Player player1;
	Vector2f curVel = { 0, 0 };
	Vector2i curPos;
	int defVel = 5;
	//const std::filesystem::path path = "Texture\Player.png"; create path frim string
	Texture texture;
	if (!texture.loadFromFile("Textures/Player05.png")) throw	runtime_error("Could not open file");
	Vector2u player1Size = texture.getSize();
	player1.init(Vector2i(winSize.x / 2, winSize.y), texture);


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
				if (event.key.code == Keyboard::D && !Keyboard::isKeyPressed(Keyboard::A))
				{
					curVel.x = defVel;
				}
				else if (event.key.code == Keyboard::A && !Keyboard::isKeyPressed(Keyboard::D))
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
		window.clear(Color::Magenta);

		// Colllision check
		curPos = player1.getPos();

		// X
		if (curPos.x + player1Size.x > winSize.x)
		{
			curVel.x = 0;
			player1.setPos(Vector2i(winSize.x - player1Size.x , curPos.y));
		}
		else if (curPos.x < 0)
		{
			curVel.x = 0;
			player1.setPos(Vector2i(0, curPos.y));
		}
		
		// Y
		if (curPos.y + player1Size.y < winSize.y)
		{
			curVel.y -= 1;
		}
		if (curPos.y + player1Size.y > winSize.y)
		{
			player1.setPos(Vector2i(curPos.x, winSize.y - player1Size.y));
			curVel.y = 0;
		}

		// Update
		player1.update(curVel);

		// Draw block
		
		mapSprite = map1.getSprites();

		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				window.draw(mapSprite[i][j]);
			}
		}

		window.draw(player1.getSprite());
		window.display();
	}
	system("exit");
}

