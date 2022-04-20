#include "Map.h"

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

sf::Sprite Map::getSprite(const sf::Vector2f pos, const sf::Vector2i offset)
{
	sf::Sprite curSprite;

	auto position = sf::Vector2f(cageSize * pos.x - offset.x, cageSize * pos.y - offset.y);
	curSprite.setPosition(position);

	if (pos.x >= map[0].size() || pos.y >= map.size() || map[pos.y][pos.x] == -1)
	{
		curSprite.setColor(sf::Color(0,0,0,0));
	}
	else
	{
		curSprite.setTexture(sheet);
		curSprite.setTextureRect(sf::IntRect((map[pos.y][pos.x]) * cageSize, 0, cageSize, cageSize));
	}
	
	return curSprite;
}
