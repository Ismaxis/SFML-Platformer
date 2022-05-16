#include "Map.h"

Map::Map(const std::string& mapPath, const std::string& sheetPath)
{
	// map
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

	// sheet
	if (!sheet.loadFromFile(sheetPath))
	{
		std::cout << "Could not open sheet" << std::endl;
	}

	cageSize = sheet.getSize().y;

	curSprite = new sf::Sprite;
	curSprite->setTexture(sheet);
}

Map::~Map()
{
	delete curSprite;
}

unsigned int Map::getCageSize() const
{
	return cageSize;
}

sf::Vector2u Map::getGridSize() const
{
	return gridSize;
}

int Map::getCage(const sf::Vector2i coords) const
{
	return map[coords.y][coords.x];
}

sf::Sprite* Map::getSprite(const sf::Vector2f pos, const sf::Vector2i offset)
{
	if (pos.x >= map[0].size() || pos.y >= map.size() || map[pos.y][pos.x] == -1)
	{
		return nullptr;
	}
	else
	{
		curSprite->setPosition(sf::Vector2f(cageSize * pos.x - offset.x, cageSize * pos.y - offset.y));
		curSprite->setTextureRect(sf::IntRect((map[pos.y][pos.x]) * cageSize, 0, cageSize, cageSize));
		return curSprite;
	}
}