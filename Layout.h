#pragma once
#include <SFML/Graphics.hpp>

class Layout
{
public:
	virtual int update(const std::vector<sf::Event>& events) = 0;
	virtual sf::Sprite getSprite() = 0;

protected:
	sf::RenderTexture texture;
	Layout() = default;
};