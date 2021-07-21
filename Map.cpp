#include "Map.h"
void Map::setMap(std::string fileName)
{
	std::vector<std::vector<int>> result;

	std::ifstream myFile(fileName, std::ios::in);

	if (!myFile.is_open())
	{
		std::cout << "Could not open txt file" << std::endl;
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

sf::Vector2<sf::Vector2<bool>> Map::isCollide(sf::Vector2i pos, sf::Vector2u size)
{
	sf::Vector2<sf::Vector2<bool>> result = { {false, false}, {false, false} };
	sf::Vector2i cage = { pos.x / cageSize, pos.y / cageSize };
	sf::Vector2u sizeInCages = { size.x / cageSize, size.y / cageSize };

	if (sizeInCages.y < cage.y < map.size())
	{
		if (sizeInCages.x < cage.x < map[cage.y].size())
		{
			// Y bottom
			if (map[cage.y][cage.x] != -1)
			{
				result.y.x = true;
			}
			// Y top
			if (map[cage.y - sizeInCages.y][cage.x] != -1)
			{
				result.y.y = true;
			}
		}
	}
	return result;
}