#include<SFML/Graphics.hpp>
#include<iostream>

#pragma once
class Player
{
private:
	sf::Vector2f plPosition;
	sf::Vector2f plVelocity = { 0, 0 };
	sf::Vector2u plSize;
	sf::Texture plTexture;
public:
	void init(sf::Vector2f pos, std::string path);

	void update(sf::Vector2f vel);

	void setPos(sf::Vector2f pos);

	sf::Vector2f getPos();

	sf::Vector2u getSize();

	sf::Sprite getSprite();
};

