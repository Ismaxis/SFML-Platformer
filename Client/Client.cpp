#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include "Layout/Layout.h"
#include "Layout/Level/Level.h"
#include "Layout/Menu/Menu.h"
#include "Layout/UpdateCode.h"
#include "Test/TestGame.h"
#include "Game/Game.h"

std::string mapPath{"Maps/map5.csv"};
std::string mapSheetPath{"Textures/mapSheet64.png"};
std::string playerTexturePath{"Textures/Player.png"};

std::pair<std::string, std::string> startButtonPaths{"Textures/startButton.png", "Textures/startButtonActive.png"};

std::pair<std::string, std::string> exitButtonPaths{"Textures/exitButton.png", "Textures/exitButtonActive.png"};
std::string pauseLabelPath{"Textures/pause.png"};
std::string emptyPath{"Textures/empty.png"};

int main(const int argc, const char* argv[])
{
    std::string ip;
    std::getline(std::ifstream("config.csv"), ip);

    sf::Vector2u winPixelSize{1920, 1080};
    sf::Vector2i winPos{0, 0};

    if (argc > 4)
    {
        winPixelSize.x = std::stoi(argv[1]);
        winPixelSize.y = std::stoi(argv[2]);
        winPos.x = std::stoi(argv[3]);
        winPos.y = std::stoi(argv[4]);
    }
    if (argc > 6)
    {
        if (strcmp(argv[5], "test") == 0)
        {
            srand(std::stoi(argv[6]));
            TestGame game(mapPath, mapSheetPath, playerTexturePath, ip, true);
            while (true)
            {
                game.update({{}, {0, 0}});
                Sleep(5);
            }
        }
    }

    sf::RenderWindow window(sf::VideoMode(winPixelSize.x - 1u, winPixelSize.y - 1u), "Game", sf::Style::Default);
    window.setFramerateLimit(144);
    window.setPosition(winPos);
    Layout* curLayout = new Menu(winPixelSize);

    while (window.isOpen())
    {
        sf::Event event{};
        Inputs input;
        std::vector<sf::Event> events;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            events.push_back(event);
        }
        input.events = events;
        input.mousePos = sf::Mouse::getPosition(window);

        UpdateCode updateCode = curLayout->update(input);
        if (updateCode == START_LEVEL)
        {
            delete curLayout;
            curLayout = new Level(mapPath, mapSheetPath, playerTexturePath, winPixelSize, ip);
            continue;
        }
        if (updateCode == EXIT_TO_MENU)
        {
            delete curLayout;
            curLayout = new Menu(winPixelSize);
            continue;
        }

        window.clear(sf::Color(255, 255, 255));
        std::queue<sf::Sprite> sprites = curLayout->getSprites();
        while (!sprites.empty())
        {
            window.draw(sprites.front());
            sprites.pop();
        }
        window.display();
    }
}
