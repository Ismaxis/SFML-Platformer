#include "Menu.h"

Menu::Menu(const sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x , winPixelSize.y);

	sf::Vector2i playBtnSize = {300, 200};
	playBtn = new Button(sf::Vector2i(winPixelSize.x/2 - playBtnSize.x/2, winPixelSize.y/2 - playBtnSize.y/2), playBtnSize);
	playBtn->setTexture(startButtonPaths.first, startButtonPaths.second);
}

Menu::~Menu()
{
	delete playBtn;
}

int Menu::update(const Inputs& input)
{
	isLmb = false;
	poolInputs(input);

	playBtn->update(input.mousePos, isLmb);

	if(playBtn->isClicked())
	{
		return START_LEVEL; // start level
	}

	return NOTHING; // nothing to do
}

sf::Sprite Menu::getSprite()
{
	// todo !!!
	// we want to remove RenderTexture
	// instead of it we will return a list of vectors
	// this vectors will draw in main loop

	texture.clear(sf::Color(60,0,100));

	texture.draw(*playBtn->getSprite());

	texture.display();
	return sf::Sprite(texture.getTexture());
}

void Menu::poolInputs(const Inputs& input)
{
	for (const auto event : input.events)
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
