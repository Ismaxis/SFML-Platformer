#include "Level.h"

Level::Level(const std::string& mapPath, const std::string& mapSheetPath, const std::string& playerTexturePath,
             const sf::Vector2u winPixelSize, const std::string& ip)
    : game(mapPath, mapSheetPath, playerTexturePath, ip),
      cam(winPixelSize, {
              game.getMap().getGridSize().x * game.getTileSize(), game.getMap().getGridSize().y * game.getTileSize()
          }),
      pauseMenu(exitButtonPaths.first, exitButtonPaths.second, pauseLabelPath, emptyPath, winPixelSize)
{
    texture.create(winPixelSize.x, winPixelSize.y);

    tileSize = game.getTileSize();
    winTileSize = {winPixelSize.x / tileSize, winPixelSize.y / tileSize + 1u};

    sf::Texture backgroundTexture;
    backgroundTexture.create(1, 1);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(winPixelSize.x, winPixelSize.y);
    backgroundSprite.setColor(sf::Color(222, 183, 247));

    offset = {0, 0};
}

Level::~Level() = default;

UpdateCode Level::update(const Inputs& input)
{
    poolInputs(input);
    if (isPause)
    {
        // update pause menu
        if (pauseMenu.update(input) == EXIT_TO_MENU)
        {
            game.unregister();
            return EXIT_TO_MENU;
        }
    }

    return game.update(input);
}

std::queue<sf::Sprite> Level::getSprites()
{
    if (game.waitingForConnection())
    {
        // waiting screen;
        return std::queue<sf::Sprite>(pauseMenu.getSprites());
    }

    offset = cam.calculateOffsets(game.getLocalPlayerPos(), game.getLocalPlayerVel());

    std::queue<sf::Sprite> result;

    result.push(backgroundSprite);

    // map
    const sf::Vector2i offsetInCages{offset.x / tileSize, offset.y / tileSize};
    for (int i = 0; i < winTileSize.y + 1; i++)
    {
        for (int j = 0; j < winTileSize.x + 1; j++)
        {
            const auto coords = sf::Vector2i(j + offsetInCages.x, i + offsetInCages.y);
            if (game.getMap().isCoordsValid(coords) && game.getMap().getCage(coords) != -1)
            {
                sf::Sprite sprite = game.getMap().getSprite(coords, offset);
                if (sprite.getTexture())
                {
                    result.push(sprite);
                }
            }
        }
    }

    // players
    for (const auto& player : game.getPlayers())
    {
        result.push(*player.second->getSprite(offset));
    }

    // pause menu
    if (isPause)
    {
        auto pauseMenuSprites = pauseMenu.getSprites();
        while (!pauseMenuSprites.empty())
        {
            result.push(pauseMenuSprites.front());
            pauseMenuSprites.pop();
        }
    }

    return result;
}

void Level::poolInputs(const Inputs& input)
{
    for (const auto event : input.events)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // esc
            if (event.key.code == sf::Keyboard::Escape)
            {
                isPause = !isPause;
            }
        }
    }
}
