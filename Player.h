#include<SFML/Graphics.hpp>
#pragma once
class Player
{
private:
	sf::Vector2i plPosition;
	sf::Vector2f plVelocity;
	sf::Vector2u plSize;
	sf::Texture plTexture;
public:
	void init(sf::Vector2i, sf::Texture);

	void update(sf::Vector2f);

	void setPos(sf::Vector2i);

	sf::Vector2i getPos();

	sf::Sprite getSprite();
};

