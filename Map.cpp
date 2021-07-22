#include "Map.h"

void Map::setMap(std::string fileName)
{
	std::vector<std::vector<int>> result;

	std::ifstream myFile(fileName, std::ios::in);

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

		result.push_back(coResult);
		coResult.clear();
	}
	myFile.close();

	map = result;
}

void Map::setPlayerSize(sf::Vector2u size)
{
	plSizeInCages = sf::Vector2u(size.x / cageSize, size.y / cageSize);
}

sf::Vector2u Map::getPlayerSize()
{
	return plSizeInCages;
}


void Map::setSheet(std::string fileName)
{
	sf::Texture texture;

	if (!texture.loadFromFile(fileName))
	{
		std::cout << "Could not open sheet" << std::endl;
	}

	sheet = texture;

	cageSize = texture.getSize().y;
}

int Map::getCageSize() 
{
	return cageSize;
}

std::vector<std::vector<sf::Sprite>> Map::getSprites()
{
	std::vector<std::vector<sf::Sprite>> result;

	for (size_t i = 0; i < map.size(); i++)
	{
		std::vector<sf::Sprite> curVector;
		for (size_t j = 0; j < map[i].size(); j++)
		{
			sf::Sprite curSprite;

			curSprite.setPosition(sf::Vector2f(cageSize * j, cageSize * i));

			curSprite.setTexture(sheet);
			int val = map[i][j];

			curSprite.setTextureRect(sf::IntRect((val + 1) * cageSize, 0, cageSize, cageSize));
			
			curVector.push_back(curSprite);
		}
		result.push_back(curVector);
	}

	return result;
}

sf::Vector2<sf::Vector2<bool>> Map::isCollide(sf::Vector2f curPos, sf::Vector2f nextPos)
{
	sf::Vector2<sf::Vector2<bool>> result = { {false, false}, {false, false} };
	sf::Vector2u nextCage = { unsigned int(nextPos.x / cageSize), unsigned int(nextPos.y / cageSize) };
	
	std::cout << nextCage.x << '\t' << nextCage.y << std::endl;

	// Y
	if (plSizeInCages.y < nextCage.y && nextCage.y < map.size())
	{
		// Y bottom
		if (map[nextCage.y][nextCage.x] != -1)
		{
			result.y.x = true;
		}
		// Y top
		if (map[nextCage.y - plSizeInCages.y][nextCage.x] != -1)
		{
			result.y.y = true;
		}

		// X
		if (1 < nextCage.x && nextCage.x + 1 < map[0].size())
		{
			for (size_t i = 0; i < plSizeInCages.x; i++)
			{
				// X left
				if (map[nextCage.y - 1 - i][nextCage.x - 1] != -1)
				{
					result.x.x = true;
				}
				// X right
				if (map[nextCage.y - 1 - i][nextCage.x + 1] != -1)
				{
					result.x.y = true;
				}
			}
		}
	}


	return result;
}