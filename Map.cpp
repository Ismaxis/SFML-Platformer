#include "Map.h"

float Map::getCageSize() const
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

sf::Sprite Map::getSprite(const sf::Vector2u pos, const sf::Vector2f offset)
{
	sf::Sprite curSprite;

	curSprite.setPosition(sf::Vector2f(cageSize * pos.x - offset.x, cageSize * pos.y - offset.y));

	
	if (pos.x >= map[0].size() || map[pos.y][pos.x] == 0)
	{
		curSprite.setColor(sf::Color(0,0,0,0));
	}
	else
	{
		curSprite.setTexture(sheet);
		curSprite.setTextureRect(sf::IntRect((map[pos.y][pos.x] - 1) * cageSize, 0, cageSize, cageSize));

	}
	
	return curSprite;
}
