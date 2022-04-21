#pragma once
#include "../Layout.h"
#include "Button.h"
#include "../updateCodes.h"

class Menu : public Layout
{
public:
	Menu(sf::Vector2u winPixelSize);

	int update(const Inputs& input) override;
	sf::Sprite getSprite() override;

private:
	Button* playBtn;
};