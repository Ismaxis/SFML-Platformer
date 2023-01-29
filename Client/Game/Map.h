#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<sstream>

class Map
{
private:
	std::vector<std::vector<int>> map;

	sf::Vector2u frameSize;
	sf::Vector2u gridSize;

	sf::Texture sheet;
	std::vector<sf::Sprite> sprites;

    int cageSize;

public:
	Map(const std::string& mapPath, const std::string& sheetPath);

	~Map();

	unsigned int getCageSize() const;

	sf::Vector2u getGridSize() const;

	bool isCoordsValid(sf::Vector2i coords) const;

	int getCage(sf::Vector2i coords) const;

	sf::Sprite getSprite(sf::Vector2i coords, sf::Vector2i offset) const;
};