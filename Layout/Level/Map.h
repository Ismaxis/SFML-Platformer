#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<sstream>

#pragma once
class Map
{
private:
	std::vector<std::vector<int>> map;

	sf::Vector2u frameSize;
	sf::Vector2u gridSize;

	sf::Texture sheet;
	sf::Sprite* curSprite;

	unsigned int cageSize;

public:
	Map(const std::string& mapPath, const std::string& sheetPath);

	~Map();

	unsigned int getCageSize() const;

	sf::Vector2u getGridSize() const;

	int getCage(sf::Vector2i coords) const;

	sf::Sprite* getSprite(sf::Vector2f pos, sf::Vector2i offset);
};