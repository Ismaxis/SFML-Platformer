#pragma once
#include "Layout.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "playerControls.h"

// draw tile map
class Level : public Layout
{
public:
	Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath, sf::Vector2u winPixelSize);

	int update(std::vector<sf::Event> events);
	sf::Sprite getSprite();

private:
	sf::Vector2i offset;
	playerControls controls;

	Player player;
	Map map;

	sf::Clock clock;

	void poolControls(std::vector<sf::Event> events);
};