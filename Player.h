#include<SFML/Graphics.hpp>
#include<iostream>
#include "Map.h"

struct CollisionInfo
{
	int collisionSide = 0;
	float availablePos = 0;
};

#pragma once
class Player
{
private:
	sf::FloatRect rect;

	sf::Vector2f plVelocity = { 0.0f, 0.0f };
	const sf::Vector2f defVel = { 0.7f, 2.3f };

	bool onGround = false;
	bool onStairs = false;

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

	void update(const Map &map, int time);

	CollisionInfo collision(const Map &map, int mode);

	void jump();

	void move(int direction);

	void grabOnStairs(int direction);

	void setPos(sf::Vector2f pos);

	sf::Vector2i getPos() const;

	bool isOnGround() const;

	bool isOnStairs() const;

	sf::Sprite getSprite(sf::Vector2i offset) const;
};