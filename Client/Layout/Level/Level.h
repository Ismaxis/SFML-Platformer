#pragma once
#include <unordered_map>

#include "../../../Server/Common.h"
#include "../Button.h"
#include "../Layout.h"
#include "../PauseMenu/PauseMenu.h"
#include "../updateCodes.h"
#include "Camera.h"
#include "Map.h"
#include "Player.h"
#include "PlayerControls.h"

extern std::pair<std::string, std::string> exitButtonPaths;
extern std::string pauseLabelPath;
extern std::string emptyPath;

// draw tile map
class Level : public Layout, olc::net::client_interface<GameMsg> {
   public:
    Level(const std::string& mapPath, const std::string& mapSheetPath,
          const std::string& playerTexturePath, sf::Vector2u winPixelSize);
    ~Level();

    int update(const Inputs& input) override;

    std::queue<sf::Sprite> getSprites() override;

   private:
    Map* map;
    unsigned int tileSize;
    sf::Vector2u gridTileSize;
    sf::Vector2u mapPixelSize;
    sf::Vector2u winTileSize;

    // Player* player;

    std::unordered_map<uint32_t, Player*> players;
    uint32_t thisPlayerID;

    std::string plStoredTexturePath;

    bool isWaitingForConnection = true;

    PlayerControls controls;

    sf::Sprite* backgroundSprite;

    Camera* cam;
    sf::Vector2i offset;

    sf::Clock clock;

    PauseMenu* pauseMenu;
    bool isPause;

    void poolInputs(const Inputs& input);
};