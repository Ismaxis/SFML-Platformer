#include<SFML/Graphics.hpp>
#include<iostream>
#include "Map.h"

#pragma once
class Player
{
private:
	sf::FloatRect rect;
	sf::Vector2f plVelocity = { 0.0f, 0.0f };
	const sf::Vector2f defVel = { 0.7f, 2.3f };
	bool onGround = false;
	sf::Texture plTexture;

public:
	Player(const std::string path)
	{
		if (!plTexture.loadFromFile(path))
		{
			std::cout << "Could not open player texture" << std::endl;
		}

		const sf::Vector2u size = plTexture.getSize();

		rect.width = size.x;
		rect.height = size.y;
	}

	void update(Map map, int time);

	void collision(Map map, int mode);

	void move(int direction);

	void jump();

	void setPos(sf::Vector2f pos);

	sf::Vector2i getPos() const;

	bool getStatus() const;

	sf::Vector2u getSize() const;

	sf::Sprite getSprite(sf::Vector2i offset) const;
};

