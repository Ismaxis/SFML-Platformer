#pragma once
#include "../Layout.h"
#include "../Button.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "playerControls.h"
#include "../updateCodes.h"

// draw tile map
class Level : public Layout
{
public:
	Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath, sf::Vector2u winPixelSize);
	~Level();

	int update(const Inputs& input) override;
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

	Button* exitBtn;
	sf::Vector2i exitBtnPos = { 20, 20 };
	sf::Vector2i exitBtnSize = { 50, 50 };
	bool isLmb;

	void  poolInputs(const Inputs& input);
};