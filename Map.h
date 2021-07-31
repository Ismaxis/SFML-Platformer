#include<SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<sstream>

#pragma once
class Map
{
private:
	std::vector<std::vector<int>> map;

	sf::Texture sheet;

	int cageSize;

public:
	Map(std::string mapPath, std::string sheetPath)
	{
		// Map
		std::ifstream myFile(mapPath, std::ios::in);

		if (!myFile.is_open())
		{
			std::cout << "Could not open txt map file" << std::endl;
		}

		std::vector<int> coResult;
		std::string line, colName;
		int val;

		while (getline(myFile, line))
		{
			std::stringstream ss(line);

			while (ss >> val)
			{
				coResult.push_back(val);

				if (ss.peek() == ',')
				{
					ss.ignore();
				}
			}
			map.push_back(coResult);
			coResult.clear();
		}
		myFile.close();

		// Sheet
		if (!sheet.loadFromFile(sheetPath))
		{
			std::cout << "Could not open sheet" << std::endl;
		}

		cageSize = sheet.getSize().y;
	}

	int getCageSize();

	sf::Vector2u getGridSize();

	int getCage(sf::Vector2i coords);

	std::vector<std::vector<sf::Sprite>> getSprites();
};