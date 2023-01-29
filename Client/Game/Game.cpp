#include "Game.h"

Game::Game(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
           const std::string& ip)
    : map(mapPath, mapSheetPath)
{
    if (client.Connect(ip, 60000))
    {
        std::cout << "Connected to " + ip + '\n';
    }

    // todo find a way to load right texture when player spawns
    plStoredTexturePath = playerTexturePath;
}

Game::~Game() = default;

UpdateCode Game::update(const Inputs& input)
{
    // Check for incoming network messages
    if (client.IsConnected())
    {
        while (!client.Incoming().empty())
        {
            auto msg = client.Incoming().pop_front().msg;

            switch (msg.header.id)
            {
            case(GameMsg::Client_Accepted):
            {
                std::cout << "Server accepted client - you're in!\n";
                olc::net::message<GameMsg> msg;
                msg.header.id = GameMsg::Client_RegisterWithServer;
                playerDescription descPlayer{{10 * map.getCageSize(), 10 * map.getCageSize()}};
                msg << descPlayer;
                client.Send(msg);
                break;
            }

            case(GameMsg::Client_AssignID):
            {
                // Server is assigning us OUR id
                msg >> thisPlayerID;
                std::cout << "Assigned Client ID = " << thisPlayerID << "\n";
                break;
            }

            case(GameMsg::Game_AddPlayer):
            {
                playerDescription desc;
                msg >> desc;

                auto newPlayer = std::make_shared<Player>(plStoredTexturePath);
                newPlayer->setPos(sf::Vector2f(desc.pos.first, desc.pos.second));

                players.insert_or_assign(desc.uniqueID, newPlayer);

                if (desc.uniqueID == thisPlayerID)
                {
                    // Now we exist in game world
                    isWaitingForConnection = false;
                }
                break;
            }

            case(GameMsg::Game_RemovePlayer):
            {
                uint32_t removalID = 0;
                msg >> removalID;
                players.erase(removalID);
                break;
            }

            case(GameMsg::Game_UpdatePlayer):
            {
                playerDescription desc;
                msg >> desc;
                if (players.find(desc.uniqueID) == players.end())
                {
                    std::cout << "Player " << desc.uniqueID << " does not exist\n";
                    break;
                }

                players[desc.uniqueID]->setPos(sf::Vector2f(desc.pos.first, desc.pos.second));
                break;
            }
            }
        }
    }

    if (isWaitingForConnection)
    {
        return WAITING_FOR_CONNECTION;
    }

    const auto posBeforeUpdate = players[thisPlayerID]->getPos();
    poolInputs(input);

    players[thisPlayerID]->move(controls.walkDirection);
    if (players[thisPlayerID]->isStairsAvailable() && controls.grabDirection != 0)
    {
        players[thisPlayerID]->grab(controls.grabDirection);
    }
    if (controls.isJump)
    {
        players[thisPlayerID]->jump();
    }

    const auto time = clock.restart().asMilliseconds();
    for (const auto& player : players)
    {
        player.second->update(map, time);
    }

    if (players[thisPlayerID]->getPos() != posBeforeUpdate || ++timeSinceLastPosUpdate > 100)
    {
        olc::net::message<GameMsg> msg;
        msg.header.id = GameMsg::Game_UpdatePlayer;
        auto pos = players[thisPlayerID]->getPos();
        const playerDescription desc{{pos.x, pos.y}, thisPlayerID};
        msg << desc;
        client.Send(msg);
        timeSinceLastPosUpdate = 0;
    }
    return NOTHING;
}

const Map& Game::getMap() const
{
    return map;
}

int Game::getTileSize() const
{
    return map.getCageSize();
}

const std::unordered_map<uint32_t, std::shared_ptr<Player>>& Game::getPlayers() const
{
    return players;
}

sf::Vector2i Game::getLocalPlayerPos()
{
    return players[thisPlayerID]->getPos();
}

sf::Vector2f Game::getLocalPlayerVel()
{
    return players[thisPlayerID]->getVel();
}

bool Game::waitingForConnection() const
{
    return isWaitingForConnection;
}

void Game::poolInputs(const Inputs& input)
{
    controls.isJump = false;

    for (const auto event : input.events)
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
            if (event.key.code == sf::Keyboard::Space && (players[thisPlayerID]->isOnGround() || players[thisPlayerID]->
                isOnStairs()))
            {
                controls.isJump = true;
            }

            // stairs grab
            if (players[thisPlayerID]->isStairsAvailable())
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
