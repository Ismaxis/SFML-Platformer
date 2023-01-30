#pragma once
#include <unordered_map>

#include "../../Server/Common.h"
#include "Map.h"
#include "Player.h"
#include "PlayerControls.h"
#include "../Layout/UpdateCode.h"
#include "../Inputs.h"

class Game
{
public:
    Game(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
         const std::string& ip);
    virtual ~Game();

    UpdateCode update(const Inputs& input);

    const Map& getMap() const;
    int getTileSize() const;
    const std::unordered_map<uint32_t, std::shared_ptr<Player>>& getPlayers() const;

    sf::Vector2i getLocalPlayerPos();
    sf::Vector2f getLocalPlayerVel();

    bool waitingForConnection() const;

    void unregister();

private:
    Map map;

    // ReSharper disable once CppInconsistentNaming
    uint32_t thisPlayerID = 0;
    std::unordered_map<uint32_t, std::shared_ptr<Player>> players;
    std::string plStoredTexturePath;

    sf::Clock clock;
    sf::Clock networkingClock;
    const int networkingRefreshRate = 60;
    const int networkingSyncTime = 1000 / networkingRefreshRate;

    olc::net::client_interface<GameMsg> client;
    bool isWaitingForConnection = true;

protected:
    PlayerControls controls;
    virtual void poolInputs(const Inputs& input);
};
