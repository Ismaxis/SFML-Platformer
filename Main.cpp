#include<SFML/Graphics.hpp>
#include<iostream>
#include<filesystem>
#include<ctime>
#include"Player.h"

using namespace sf;
using namespace std;

int main()
{	
	const Vector2u winSize = { 960, 540 };
	RenderWindow window(VideoMode(winSize.x, winSize.y), "SFML window", Style::Default);
	window.setFramerateLimit(60);

	Player player1;
	Vector2f curVel = { 0, 0 };
	Vector2i curPos;
	int defVel = 5;

	//const std::filesystem::path path = "Texture\Player.png"; create path frim string
	Texture texture;
	if (!texture.loadFromFile("Textures/Player.png"))
	{
		cout << "Texture load failed!" << endl;
		return 0;
	}

	Vector2u player1Size = texture.getSize();
	player1.init(Vector2i(winSize.x/2, winSize.y), texture);

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
				if (event.key.code == Keyboard::D)
				{
					curVel.x = defVel;
				}
				else if (event.key.code == Keyboard::A)
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
		window.draw(player1.getSprite());

		window.display();
	}
	system("exit");
}

