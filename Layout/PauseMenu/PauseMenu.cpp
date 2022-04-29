#include "PauseMenu.h"

#include <iostream>

PauseMenu::PauseMenu(const std::string& exitBtnPassive, const std::string& exitBtnActive, const std::string& pauseLabelPath, sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x, winPixelSize.y);

	exitButton = new Button(exitBtnPos, exitBtnSize);
	exitButton->setTexture(exitBtnPassive, exitBtnActive);

	if(!pauseLabelTexture.loadFromFile(pauseLabelPath))
	{
		std::cout << "Could not open pauseLabel texture";
	}

	pauseLabelPos = {winPixelSize.x / 2 - pauseLabelSize.x / 2, winPixelSize.y / 2 - pauseLabelSize.y / 2};
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

sf::Sprite PauseMenu::getSprite()
{
	// clear and fill with transparent black
	texture.clear(sf::Color(0,0,0,100));

	// draw button
	texture.draw(exitButton->getSprite());

	// draw label
	const sf::Vector2u textureSize = pauseLabelTexture.getSize();
	sf::Sprite labelSprite(pauseLabelTexture);
	labelSprite.setPosition(pauseLabelPos.x, pauseLabelPos.y);
	labelSprite.setScale(pauseLabelSize.x / textureSize.x, pauseLabelSize.y / textureSize.y);
	texture.draw(labelSprite);

	texture.display();
	return sf::Sprite(texture.getTexture());
}

void PauseMenu::poolInputs(const Inputs& input)
{
	for (const auto& event : input.events)
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