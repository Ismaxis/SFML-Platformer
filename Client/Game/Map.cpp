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

	for (int i = 0; i < sheet.getSize().x; i += cageSize)
	{
		sf::Sprite newSprite(sheet);
		newSprite.setTextureRect(sf::IntRect(i, 0, cageSize, cageSize));
		sprites.push_back(newSprite);
	}
}

Map::~Map() = default;

unsigned int Map::getCageSize() const
{
	return cageSize;
}

sf::Vector2u Map::getGridSize() const
{
	return gridSize;
}

bool Map::isCoordsValid(const sf::Vector2i coords) const
{
	if (coords.x >= map[0].size() || coords.y >= map.size())
	{
		return false;
	}
	return true;
}

int Map::getCage(const sf::Vector2i coords) const
{
	return map[coords.y][coords.x];
}

sf::Sprite Map::getSprite(const sf::Vector2i coords, const sf::Vector2i offset) const
{
	sf::Sprite curSprite(sprites[getCage(coords)]);

	const auto position = sf::Vector2f(static_cast<float>(static_cast<int>(cageSize) * coords.x - offset.x), 
	                                   static_cast<float>(static_cast<int>(cageSize) * coords.y - offset.y));
	curSprite.setPosition(position);
	return curSprite;
}