#pragma once
#include <SFML/Graphics.hpp>
#include "Inputs.h"

class Layout
{
public:
	virtual int update(const Inputs& input) = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual ~Layout() = default; 
	// its important to have a virtual destructor in base abstract class

protected:
	sf::RenderTexture texture;
	Layout() = default;
};