#include<SFML/Graphics.hpp>
#include<iostream>
#pragma once
class Player
{
private:
	sf::Vector2i plPosition;
	sf::Vector2f plVelocity;
	sf::Vector2u plSize;
	sf::Texture plTexture;
	bool onGround;
public:
	void init(sf::Vector2i, std::string path);

	void update(sf::Vector2f);

	void setPos(sf::Vector2i);

	void setStatus(bool status);

	sf::Vector2i getPos();
	
	bool getStatus();

	sf::Vector2u getSize();

	sf::Sprite getSprite();
};

