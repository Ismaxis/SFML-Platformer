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
	Player(std::string path)
	{
		if (!plTexture.loadFromFile(path))
		{
			std::cout << "Could not open player texture" << std::endl;
		}

		plSize = plTexture.getSize();
	}

	void update();

	void setPos(sf::Vector2f pos);

	sf::Vector2f getPos();

	void setVel(sf::Vector2f vel);

	sf::Vector2f getVel();

	sf::Vector2u getSize();

	sf::Sprite getSprite();
};

