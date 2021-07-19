#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>

using namespace sf;
using namespace std;

int main()
{	
	const Vector2u winSize = { 1920, 1080 };
	RenderWindow window(VideoMode(winSize.x, winSize.y), "SFML window", Style::Fullscreen);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		// Clear
		window.clear(Color::White);

		// Update

		// Draw block
	}
	system("exit");
}

