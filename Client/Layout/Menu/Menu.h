#pragma once
#include "../Layout.h"
#include "../Button.h"
#include "../updateCodes.h"

extern std::pair<std::string, std::string> startButtonPaths;

class Menu : public Layout
{
public:
	Menu(sf::Vector2u winPixelSize);
	~Menu();

	int update(const Inputs& input) override;

	std::queue<sf::Sprite> getSprites() override;

private:
	Button* playBtn;
	bool isLmb;

	sf::Sprite* backgroundSprite;

	void poolInputs(const Inputs& input);
};