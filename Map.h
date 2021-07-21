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

	int cageSize;

	std::vector<std::vector<int>> map;

public:
	void setMap(std::string fileName);

	void setSheet(std::string fileName);

	std::vector<std::vector<sf::Sprite>> getSprites();

	bool isCollide(sf::Vector2i pos);
};

