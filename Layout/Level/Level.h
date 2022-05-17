#pragma once
#include "../Layout.h"
#include "../Button.h"
#include "Map.h"
#include "Player.h"
#include "Camera.h"
#include "playerControls.h"
#include "../updateCodes.h"
#include "../PauseMenu/PauseMenu.h"

extern std::pair<std::string,std::string> exitButtonPaths;
extern std::string pauseLabelPath;
extern std::string pauseBackgroundPath;

// draw tile map
class Level : public Layout
{
public:
	Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,  sf::Vector2u winPixelSize);
	~Level();

	int update(const Inputs& input) override;
	sf::Sprite getSprite() override;

	std::queue<sf::Sprite> getSprites() override;

private:
	Map* map;
	unsigned int tileSize;
	sf::Vector2u gridTileSize;
	sf::Vector2u mapPixelSize; 
	sf::Vector2u winTileSize;

	Player* player;
	playerControls controls;

	sf::Sprite* backgroundSprite;

	Camera* cam; 
	sf::Vector2i offset;

	sf::Clock clock;

	PauseMenu* pauseMenu;
	bool isPause;

	void poolInputs(const Inputs& input);
};