#include "Level.h"

Level::Level(const std::string& mapPath, const std::string& mapSheetPath,
             const std::string& playerTexturePath,
             const sf::Vector2u winPixelSize) {
    if (Connect("127.0.0.1", 60000))  // 194.67.111.111
    {
        std::cout << "Connected\n";
    }

    texture.create(winPixelSize.x, winPixelSize.y);

    map = new Map(mapPath, mapSheetPath);
    tileSize = map->getCageSize();
    gridTileSize = map->getGridSize();
    mapPixelSize = {gridTileSize.x * tileSize, gridTileSize.y * tileSize};
    winTileSize = {winPixelSize.x / tileSize, winPixelSize.y / tileSize + 1u};

    // todo find a way to load right texture when player adds to game
    plStoredTexturePath = playerTexturePath;
    // player = new Player(playerTexturePath);
    // player->setPos(sf::Vector2f(10 * tileSize, 20 * tileSize)); // todo
    // initial position of player

    sf::Texture backgroundTexture;
    backgroundTexture.create(1, 1);
    backgroundSprite = new sf::Sprite(backgroundTexture);
    backgroundSprite->setScale(winPixelSize.x, winPixelSize.y);
    backgroundSprite->setColor(sf::Color(222, 183, 247));

    cam = new Camera(winPixelSize, mapPixelSize);
    offset = {0, 0};

    pauseMenu = new PauseMenu(exitButtonPaths.first, exitButtonPaths.second,
                              pauseLabelPath, emptyPath, winPixelSize);
    isPause = false;
}

Level::~Level() {
    delete map;
    delete cam;
    delete pauseMenu;
    for (const auto& player : players) {
        delete player.second;
    }
}

int Level::update(const Inputs& input) {
    // Check for incoming network messages
    if (IsConnected()) {
        while (!Incoming().empty()) {
            auto msg = Incoming().pop_front().msg;

            switch (msg.header.id) {
                case (GameMsg::Client_Accepted): {
                    std::cout << "Server accepted client - you're in!\n";
                    olc::net::message<GameMsg> msg;
                    msg.header.id = GameMsg::Client_RegisterWithServer;
                    playerDescription descPlayer{{10 * tileSize, 10 * tileSize},
                                                 {0.f, 0.f}};
                    msg << descPlayer;
                    Send(msg);
                    break;
                }

                case (GameMsg::Client_AssignID): {
                    // Server is assigning us OUR id
                    msg >> thisPlayerID;
                    std::cout << "Assigned Client ID = " << thisPlayerID
                              << "\n";
                    break;
                }

                case (GameMsg::Game_AddPlayer): {
                    playerDescription desc;
                    msg >> desc;

                    Player* newPlayer = new Player(plStoredTexturePath);
                    newPlayer->setPos(
                        sf::Vector2f(desc.pos.first, desc.pos.second));
                    newPlayer->setVel(
                        sf::Vector2f(desc.vel.first, desc.vel.second));

                    players.insert_or_assign(desc.uniqueID, newPlayer);

                    if (desc.uniqueID == thisPlayerID) {
                        // Now we exist in game world
                        isWaitingForConnection = false;
                    }
                    break;
                }

                case (GameMsg::Game_RemovePlayer): {
                    uint32_t nRemovalID = 0;
                    msg >> nRemovalID;
                    players.erase(nRemovalID);
                    break;
                }

                case (GameMsg::Game_UpdatePlayer): {
                    playerDescription desc;
                    msg >> desc;
                    if (players.find(desc.uniqueID) == players.end()) {
                        std::cout << "Player " << desc.uniqueID
                                  << " does not exist\n";
                        break;
                    }

                    players[desc.uniqueID]->setPos(
                        sf::Vector2f(desc.pos.first, desc.pos.second));
                    players[desc.uniqueID]->setVel(
                        sf::Vector2f(desc.vel.first, desc.vel.second));
                    break;
                }
            }
        }
    }

    if (isWaitingForConnection) {
        return NOTHING;
    }

    // Local updates

    // THIS player inputs
    poolInputs(input);

    if (isPause) {
        // update pause menu
        if (pauseMenu->update(input) == EXIT_TO_MENU) {
            return EXIT_TO_MENU;
        }
    } else {
        // move THIS player
        players[thisPlayerID]->move(controls.walkDirection);

        if (players[thisPlayerID]->isStairsAvailable() &&
            controls.grabDirection != 0) {
            players[thisPlayerID]->grab(controls.grabDirection);
        }

        if (controls.isJump) {
            players[thisPlayerID]->jump();
        }
    }

    // update all players
    auto timeElapsed = clock.restart().asMilliseconds();
    for (auto& player : players) {
        player.second->update(*map, timeElapsed);
    }

    // Send player description
    olc::net::message<GameMsg> msg;
    msg.header.id = GameMsg::Game_UpdatePlayer;
    auto pos = players[thisPlayerID]->getPos();
    auto vel = players[thisPlayerID]->getVel();
    const playerDescription desc{{pos.x, pos.y}, {vel.x, vel.y}, thisPlayerID};
    msg << desc;
    Send(msg);

    return NOTHING;  // nothing to do
}

std::queue<sf::Sprite> Level::getSprites() {
    if (isWaitingForConnection) {
        // waiting screen;
        return std::queue<sf::Sprite>(pauseMenu->getSprites());
    }

    offset = cam->calculateOffsets(players[thisPlayerID]->getPos(),
                                   players[thisPlayerID]->getVel());

    std::queue<sf::Sprite> result;

    result.push(*backgroundSprite);

    // map
    const sf::Vector2i offsetInCages{static_cast<int>(offset.x / tileSize),
                                     static_cast<int>(offset.y / tileSize)};
    for (float i = 0; i < winTileSize.y + 1; i++) {
        for (float j = 0; j < winTileSize.x + 1; j++) {
            const auto coords =
                sf::Vector2i(j + offsetInCages.x, i + offsetInCages.y);
            if (map->isCoordsValid(coords) && map->getCage(coords) != -1) {
                sf::Sprite sprite = map->getSprite(coords, offset);
                if (sprite.getTexture()) {
                    result.push(sprite);
                }
            }
        }
    }

    // players
    for (auto& player : players) {
        result.push(*player.second->getSprite(offset));
    }

    // pause menu
    if (isPause) {
        auto pauseMenuSprites = pauseMenu->getSprites();
        while (!pauseMenuSprites.empty()) {
            result.push(pauseMenuSprites.front());
            pauseMenuSprites.pop();
        }
    }

    return result;
}

void Level::poolInputs(const Inputs& input) {
    controls.isJump = false;

    for (const auto event : input.events) {
        // keyboard
        if (event.type == sf::Event::KeyPressed) {
            // x movement
            if (event.key.code == sf::Keyboard::D) {
                controls.walkDirection = 1;
            } else if (event.key.code == sf::Keyboard::A) {
                controls.walkDirection = -1;
            }

            // jump
            if (event.key.code == sf::Keyboard::Space &&
                (players[thisPlayerID]->isOnGround() ||
                 players[thisPlayerID]->isOnStairs())) {
                controls.isJump = true;
            }

            // stairs grab
            if (players[thisPlayerID]->isStairsAvailable()) {
                if (event.key.code == sf::Keyboard::W) {
                    controls.grabDirection = -1;
                } else if (event.key.code == sf::Keyboard::S) {
                    controls.grabDirection = 1;
                }
            }

            // esc
            if (event.key.code == sf::Keyboard::Escape) {
                isPause = !isPause;
            }
        }
        // keyboard hold
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            controls.walkDirection = 0;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            controls.grabDirection = 0;
        }
    }
}
