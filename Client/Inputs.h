#pragma once
#include <SFML/Graphics.hpp>

struct Inputs
{
	std::vector<sf::Event> events;
	sf::Vector2i mousePos;
};
