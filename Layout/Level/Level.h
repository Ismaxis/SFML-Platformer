#pragma once
#include "../Layout.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "playerControls.h"

// draw tile map
class Level : public Layout
{
public:
	Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath, sf::Vector2u winPixelSize);

	int update(const std::vector<sf::Event>& events) override;
	sf::Sprite getSprite() override;

private:
	Map* map;
	unsigned int tileSize;
	sf::Vector2u gridTileSize;
	sf::Vector2u mapPixelSize;
	sf::Vector2u winTileSize;

	Player* player;
	int direction{ 0 }; 
	int grabDirection{ 0 }; 
	playerControls controls;

	Camera* cam; 
	sf::Vector2i offset;

	sf::Clock clock;

	void poolControls(const std::vector<sf::Event>& events);
};