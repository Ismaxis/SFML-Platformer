#pragma once
#include <unordered_map>

#include "../../Server/Common.h"
#include "Map.h"
#include "Player.h"
#include "PlayerControls.h"
#include "../Layout/UpdateCode.h"
#include "../Inputs.h"

struct Inputs;

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

private:
    Map map;

    // ReSharper disable once CppInconsistentNaming
    uint32_t thisPlayerID = 0;
    std::unordered_map<uint32_t, std::shared_ptr<Player>> players;
    std::string plStoredTexturePath;

    sf::Clock clock;
    int timeSinceLastPosUpdate = 0;


    olc::net::client_interface<GameMsg> client;
    bool isWaitingForConnection = true;

protected:
    PlayerControls controls;
    virtual void poolInputs(const Inputs& input);
};
