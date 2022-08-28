#pragma once
#include <queue>
#include <SFML/Graphics.hpp>
#include "Inputs.h"

class Layout
{
public:
	virtual int update(const Inputs& input) = 0;
	virtual std::queue<sf::Sprite> getSprites() = 0;

	virtual ~Layout() = default; // its important to have a virtual destructor in base abstract class

protected:
	sf::RenderTexture texture;
	Layout() = default;
};