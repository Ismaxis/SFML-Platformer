#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#pragma once
class Map
{
private:
	sf::Texture sheet;

	sf::Vector2u plSizeInCages;

	int cageSize;

	std::vector<std::vector<int>> map;

public:
	void setMap(std::string fileName);

	void setPlayerSize(sf::Vector2u plSize);

	sf::Vector2u getPlayerSize();

	void setSheet(std::string fileName);

	int getCageSize();

	std::vector<std::vector<sf::Sprite>> getSprites();

	sf::Vector2<sf::Vector2<bool>> isCollide(sf::Vector2f pos);
};

