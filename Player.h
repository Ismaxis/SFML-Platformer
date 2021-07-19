#include<SFML/Graphics.hpp>
#include"PlayerInfo.h"
#pragma once
class Player
{
private:
	sf::Vector2i position;
	sf::Vector2f velocity;
	sf::Vector2u size;
	sf::Texture texture;
public:
	void update();
	
	PlayerInfo getInfo();

	sf::Sprite* draw(sf::Vector2u winSize);
};

