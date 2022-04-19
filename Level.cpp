#include "Level.h"

Level::Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath ,sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x, winPixelSize.y);

	map = new Map(mapPath, mapSheetPath);
	player = new Player(playerTexturePath);
}

int Level::update(std::vector<sf::Event> events)
{
	controls.isJump = false;

	poolControls(events);

	if(controls.walkDirection != 0)
	{
		player->move(controls.walkDirection);
	}
		
	if (player->isStairsAvailable() && controls.grabDirection != 0)
	{
		player->grab(controls.grabDirection);
	}

	if (controls.isJump)
	{
		player->jump();
	}

	player->update(*map, clock.restart().asMilliseconds());

	return 0; // nothing to do
}

void Level::poolControls(std::vector<sf::Event> events)
{
	for(auto event : events)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			// X movement
			if (event.key.code == sf::Keyboard::D)
			{
				controls.walkDirection = 1;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				controls.grabDirection = -1;
			}

			// Jump 
			if (event.key.code == sf::Keyboard::Space && (player->isOnGround() || player->isOnStairs()))
			{
				controls.isJump = true;
			}

			// Stairs grab
			if (player->isStairsAvailable())
			{
				if (event.key.code == sf::Keyboard::W)
				{
					controls.grabDirection = -1;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					controls.grabDirection = 1;
				}
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			controls.walkDirection = 0;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			controls.grabDirection = 0;
		}
	}
}
