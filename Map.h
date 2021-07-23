#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

#pragma once
class Map
{
private:
	int cageSize;
	
	sf::Texture sheet;

	sf::Vector2u plSizeInCages;

	std::vector<std::vector<int>> map;

public:
	Map(std::string mapPath, std::string sheetPath, sf::Vector2u plSize)
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

		// Size
		plSizeInCages = sf::Vector2u(plSize.x / cageSize, plSize.y / cageSize);
	}

	sf::Vector2u getPlayerSize();

	int getCageSize();

	std::vector<std::vector<sf::Sprite>> getSprites();

	sf::Vector2<sf::Vector2<bool>> isCollide(sf::Vector2f curPos, sf::Vector2f nextPos);
};