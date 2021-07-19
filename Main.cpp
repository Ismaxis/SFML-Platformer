#include<SFML/Graphics.hpp>
#include<iostream>
#include<filesystem>
#include<ctime>
#include"Player.h"
#include"PlayerInfo.h"

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
				if (Keyboard::isKeyPressed(Keyboard::D))
				{
					curVel.x = defVel;
				}
				else if (Keyboard::isKeyPressed(Keyboard::A))
				{
					curVel.x = -defVel;
				}
			}
			if (event.type == Event::KeyReleased)
			{
				curVel.x = 0;
			}
		}

		// Clear
		window.clear(Color::White);

		// Colllision check
		curPos = player1.getPos();
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

		// Update
		player1.update(curVel);

		// Draw block
		window.draw(player1.getSprite());

		window.display();
	}
	system("exit");
}

