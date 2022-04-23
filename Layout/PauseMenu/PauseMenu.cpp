#include "PauseMenu.h"

PauseMenu::PauseMenu(const std::string& exitBtnPassive, const std::string& exitBtnActive, sf::Vector2u winPixelSize)
{
	texture.create(winPixelSize.x, winPixelSize.y);

	exitButton = new Button(exitBtnPos, exitBtnSize);
	exitButton->setTexture(exitBtnPassive, exitBtnActive);
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