#include "Map.h"

sf::Vector2u Map::getPlayerSize()
{
	return plSizeInCages;
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
	
	//std::cout << nextCage.x << '\t' << nextCage.y << std::endl;

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