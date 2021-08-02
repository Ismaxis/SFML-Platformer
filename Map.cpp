#include "Map.h"

int Map::getCageSize() const
{
	return cageSize;
}

sf::Vector2u Map::getGridSize() const
{
	return gridSize;
}

int Map::getCage(const sf::Vector2i coords)
{
	return map[coords.y][coords.x];
}

std::vector<std::vector<sf::Sprite>> Map::getSprites(const sf::Vector2f offset)
{
	std::vector<std::vector<sf::Sprite>> result;

	sf::Vector2f cageOffset{ offset.x / cageSize, offset.y / cageSize };
	
	for (int i = 0; i < map.size(); i++)
	{
		std::vector<sf::Sprite> curVector;
		for (int j = 0; j < map[i].size(); j++)
		{
			sf::Sprite curSprite;

			curSprite.setPosition(sf::Vector2f(cageSize * j - offset.x, cageSize * i - offset.y));

			curSprite.setTexture(sheet);

			curSprite.setTextureRect(sf::IntRect((map[i][j]) * cageSize, 0, cageSize, cageSize));
			
			curVector.push_back(curSprite);
		}
		result.push_back(curVector);
	}

	return result;
}