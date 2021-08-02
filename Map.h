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

	float cageSize;

public:
	Map(const std::string mapPath, const std::string sheetPath)
	{
		// Map
		std::ifstream file(mapPath, std::ios::in);

		if (!file.is_open())
		{
			std::cout << "Could not open txt map file" << std::endl;
		}

		std::vector<int> coResult;
		std::string line, colName;

		while (getline(file, line))
		{
			std::stringstream ss(line);
			int val;
			
			while (ss >> val)
			{
				coResult.push_back(val);

				if (ss.peek() == ',')
				{
					ss.ignore();
				}
			}
			map.push_back(coResult);
			gridSize = sf::Vector2u(map[0].size(), map.size());
			coResult.clear();
		}
		file.close();

		// Sheet
		if (!sheet.loadFromFile(sheetPath))
		{
			std::cout << "Could not open sheet" << std::endl;
		}

		cageSize = sheet.getSize().y;
	}

	float getCageSize() const;

	sf::Vector2u getGridSize() const;

	int getCage(sf::Vector2i coords);

	std::vector<std::vector<sf::Sprite>> getSprites(sf::Vector2f offset);

	sf::Sprite getSprite(sf::Vector2u pos, sf::Vector2f offset);
};