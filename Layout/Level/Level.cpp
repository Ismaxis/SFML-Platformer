#include "Level.h"

Level::Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath, const sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x, winPixelSize.y);

	map = new Map(mapPath, mapSheetPath);
	tileSize = map->getCageSize();
	gridTileSize = map->getGridSize();
	mapPixelSize = { gridTileSize.x * tileSize, gridTileSize.y * tileSize };
	winTileSize = { winPixelSize.x / tileSize, winPixelSize.y / tileSize + 1u };

	player = new Player(playerTexturePath);
	player->setPos(sf::Vector2f(10 * tileSize, 20 * tileSize)); // todo initial position of player
	controls.walkDirection = 0;
	controls.grabDirection = 0;

	sf::Texture backgroundTexture;
	backgroundTexture.create(1,1);
	backgroundSprite = new sf::Sprite(backgroundTexture);
	backgroundSprite->setScale(winPixelSize.x, winPixelSize.y);
	backgroundSprite->setColor(sf::Color(222, 183, 247));

	cam = new Camera(winPixelSize, mapPixelSize);
	offset = { 0, 0 };

	pauseMenu = new PauseMenu(exitButtonPaths.first, exitButtonPaths.second, pauseLabelPath, winPixelSize);
}

Level::~Level()
{
	delete map;
	delete player;
	delete cam;
	delete pauseMenu;
}

int Level::update(const Inputs& input)
{
	poolInputs(input);

	if(isPause)
	{
		// update pause menu
		if(pauseMenu->update(input) == EXIT_TO_MENU)
		{
			return EXIT_TO_MENU;	
		}		
	}
	else
	{
		// move player
		player->move(controls.walkDirection);

		if (player->isStairsAvailable() && controls.grabDirection != 0)
		{
			player->grab(controls.grabDirection);
		}

		if (controls.isJump)
		{
			player->jump();
		}
	}
	// update player
	player->update(*map, clock.restart().asMilliseconds());

	return NOTHING; // nothing to do
}

sf::Sprite Level::getSprite()
{
	// clear
	texture.clear(sf::Color(222, 183, 247));

	// generation offsets
	offset = cam->calculateOffsets(player->getPos(), player->getVel());

	// map draw
	const sf::Vector2i offsetInCages{ static_cast<int> (offset.x / tileSize), static_cast<int> (offset.y / tileSize) };
	for (float i = 0; i < winTileSize.y + 1; i++)
	{
		for (float j = 0; j < winTileSize.x + 1; j++)
		{
			const sf::Sprite* sprite = map->getSprite(sf::Vector2f(j + offsetInCages.x, i + offsetInCages.y), offset);
			if(sprite != nullptr)
			{
				texture.draw(*sprite);
			}
		}
	}

	// player draw
	texture.draw(*player->getSprite(offset));

	// pause menu draw
	if(isPause)
	{
		texture.draw(pauseMenu->getSprite());
	}

	texture.display();
	return sf::Sprite(texture.getTexture());
}

std::queue<sf::Sprite*> Level::getSprites()
{
	offset = cam->calculateOffsets(player->getPos(), player->getVel());

	std::queue<sf::Sprite*> result;

	result.push(new sf::Sprite(*backgroundSprite));

	// map
	const sf::Vector2i offsetInCages{ static_cast<int> (offset.x / tileSize), static_cast<int> (offset.y / tileSize) };
	for (float i = 0; i < winTileSize.y + 1; i++)
	{
		for (float j = 0; j < winTileSize.x + 1; j++)
		{
			sf::Sprite* sprite = map->getSprite(sf::Vector2f(j + offsetInCages.x, i + offsetInCages.y), offset);
			if(sprite != nullptr)
			{
				result.push(new sf::Sprite(*sprite));
			}
		}
	}

	// player
	result.push(new sf::Sprite(*player->getSprite(offset)));

	// pause menu
	if(isPause)
	{
		auto pauseMenuSprites = pauseMenu->getSprites();
		while(!pauseMenuSprites.empty())
		{
			result.push(new sf::Sprite(*pauseMenuSprites.front()));
			pauseMenuSprites.pop();
		}
	}

	return result;
}

void Level::poolInputs(const Inputs& input)
{
	controls.isJump = false;

	for(const auto event : input.events)
	{
		// keyboard
		if (event.type == sf::Event::KeyPressed)
		{
			// x movement
			if (event.key.code == sf::Keyboard::D)
			{
				controls.walkDirection = 1;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				controls.walkDirection = -1;
			}

			// jump 
			if (event.key.code == sf::Keyboard::Space && (player->isOnGround() || player->isOnStairs()))
			{
				controls.isJump = true;
			}

			// stairs grab
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

			// esc
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					isPause = !isPause;
				}
			}
		}
		// keyboard hold
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
