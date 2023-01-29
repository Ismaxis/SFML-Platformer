#pragma once
#include <unordered_map>

#include "../Layout.h"
#include "../Button.h"
#include "Camera.h"
#include "../PauseMenu/PauseMenu.h"
#include "../../../Server/Common.h"
#include "../../Game/Game.h"

extern std::pair<std::string, std::string> exitButtonPaths;
extern std::string pauseLabelPath;
extern std::string emptyPath;

class Level : public Layout
{
public:
    Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
          sf::Vector2u winPixelSize, const std::string& ip);
    ~Level() override;

    UpdateCode update(const Inputs& input) override;

    std::queue<sf::Sprite> getSprites() override;

private:
    Game game;

    int tileSize;
    sf::Vector2u winTileSize;

    sf::Sprite backgroundSprite;

    Camera cam;
    sf::Vector2i offset;

    PauseMenu pauseMenu;
    bool isPause = false;

    void poolInputs(const Inputs& input);
};
