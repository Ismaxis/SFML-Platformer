#pragma once
#include "../Layout.h"
#include "../Button.h"
#include "../updateCodes.h"
class PauseMenu : public Layout
{
public:
	PauseMenu(const std::string& exitBtnPassive, const std::string& exitBtnActive, const std::string& pauseLabelPath, sf::Vector2u winPixelSize);

	~PauseMenu();

	int update(const Inputs& input) override;
	sf::Sprite getSprite() override;
	std::queue<sf::Sprite*> getSprites() override;

private:
	Button* exitButton;
	sf::Vector2i exitBtnPos = { 20, 20 };
	sf::Vector2i exitBtnSize = { 50, 50 };
	bool isLmb;

	sf::Texture pauseLabelTexture;
	sf::Sprite* labelSprite;
	sf::Vector2u pauseLabelPos;
	sf::Vector2i pauseLabelSize = { 800, 400 };

	sf::Sprite* backgroundSprite;

	void poolInputs(const Inputs& input);
};