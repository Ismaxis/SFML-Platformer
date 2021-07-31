#include<SFML/Graphics.hpp>
#include<iostream>
#include "Map.h"

#pragma once
class Player
{
private:
	sf::FloatRect Rect;
	sf::Vector2f plVelocity = { 0.0f, 0.0f };
	const sf::Vector2f defVel = { 0.333f, 1.333f };
	bool onGround = false;
	sf::Texture plTexture;

public:
	Player(std::string path)
	{
		if (!plTexture.loadFromFile(path))
		{
			std::cout << "Could not open player texture" << std::endl;
		}

		sf::Vector2u size = plTexture.getSize();

		Rect.width = size.x;
		Rect.height = size.y;
	}

	void update(Map map, float time);

	void Collision(Map map, int mode);

	void Move(int direction);

	void Jump();

	void setPos(sf::Vector2f pos);

	sf::Vector2f getPos();

	bool getStatus();

	sf::Vector2u getSize();

	sf::Sprite getSprite();
};

