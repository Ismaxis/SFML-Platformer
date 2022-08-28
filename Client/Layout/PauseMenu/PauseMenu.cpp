#include "PauseMenu.h"

#include <iostream>

PauseMenu::PauseMenu(const std::string& exitBtnPassive, const std::string& exitBtnActive, const std::string& pauseLabelPath, const std::string& emptyPath, sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x, winPixelSize.y);

	exitButton = new Button(exitBtnPos, exitBtnSize);
	exitButton->setTexture(exitBtnPassive, exitBtnActive);

	if(!pauseLabelTexture.loadFromFile(pauseLabelPath))
	{
		std::cout << "Could not open pauseLabel texture";
	}

	pauseLabelPos = {winPixelSize.x / 2 - pauseLabelSize.x / 2, winPixelSize.y / 2 - pauseLabelSize.y / 2};

	labelSprite = new sf::Sprite(pauseLabelTexture);
	const sf::Vector2u textureSize = pauseLabelTexture.getSize();
	labelSprite->setPosition(pauseLabelPos.x, pauseLabelPos.y);
	labelSprite->setScale(pauseLabelSize.x / textureSize.x, pauseLabelSize.y / textureSize.y);
	
	backgroundTexture.loadFromFile(emptyPath);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(0,0,0,100));
	backgroundSprite.setScale(winPixelSize.x, winPixelSize.y);
}

PauseMenu::~PauseMenu()
{
	delete exitButton;
	delete labelSprite;
}

int PauseMenu::update(const Inputs& input)
{
	isLmb = false;

	poolInputs(input);

	// update
	exitButton->update(input.mousePos, isLmb);

	if(exitButton->isClicked())
	{
		return EXIT_TO_MENU;
	}

	return NOTHING;
}

std::queue<sf::Sprite> PauseMenu::getSprites()
{
	std::queue<sf::Sprite> result;
	result.push(backgroundSprite);
	result.push(*exitButton->getSprite());
	result.push(*labelSprite);

	return result;
}

void PauseMenu::poolInputs(const Inputs& input)
{
	for (auto& event : input.events)
	{
		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				isLmb = true;
			}
		}
	}
}
