#include "Player.h"

void Player::update(const Map &map, int time)
{
	// Frame time limit
	if (time > 10)
	{
		time = 10;
	}
	
	// X
	rect.left += plVelocity.x * time;
	const CollisionInfo hCol = collisionX(map);
	
	if (hCol.collisionSide == -1)
	{
		rect.left = hCol.availablePos;
	}
	else if(hCol.collisionSide == 1)
	{
		rect.left = hCol.availablePos;
	}
	
	// Y
	plVelocity.y += time * 0.008f;

	rect.top += plVelocity.y * time;

	isNowOnStairs = false;
	onGround = false;

	// Checking is player staying on top of the stair
	const CollisionInfo bottomStairsCol = bottomStairsCollisionY(map);
	
	const CollisionInfo vCol = collisionY(map);

	if (vCol.collisionSide == -1)
	{
		stairsAvailable = false;
		rect.top = vCol.availablePos;
		plVelocity.y = 0;
		onGround = true;
	}
	else if (vCol.collisionSide == 1)
	{
		rect.top = vCol.availablePos;
		plVelocity.y = 0;
	}
	else if(bottomStairsCol.collisionSide == -1)
	{
		stairsAvailable = true;
		rect.top = bottomStairsCol.availablePos;
		plVelocity.y = 0;
		onGround = true;
	}
	
	plVelocity.x = 0;
}

CollisionInfo Player::collisionX(const Map& map) const
{
	const int cageSize = map.getCageSize();
	const sf::Vector2f topLeftCage = { rect.left / cageSize, rect.top / cageSize };
	const sf::Vector2f bottomRightCage = { (rect.left + rect.width) / cageSize, (rect.top + rect.height) / cageSize };
	
	CollisionInfo result = singleCollisionX(topLeftCage.y, bottomRightCage.y, map, topLeftCage.x, cageSize);

	if (result.collisionSide != 0)
	{
		return result;
	}

	result = singleCollisionX(topLeftCage.y, bottomRightCage.y, map, bottomRightCage.x, cageSize);
	return result;
}

CollisionInfo Player::singleCollisionX(const float top, const float bottom, const Map& map, const int x, const int& cageSize) const
{
	CollisionInfo result;
	// left
	for (int y = top; y < bottom; y++)
	{
		const int curCage = map.getCage(sf::Vector2i(x, y));
		
		// Collision check
		if (isBlock(curCage))
		{
			// right
			if (plVelocity.x > 0)
			{
				result.collisionSide = -1;
				result.availablePos = x * cageSize - rect.width;
			}
			
			// left
			if (plVelocity.x < 0)
			{
				result.collisionSide = 1;
				result.availablePos = (x + 1) * cageSize;
			}
		}
	}
	return result;
}

CollisionInfo Player::collisionY(const Map& map) const
{
	const int cageSize = map.getCageSize();
	const sf::Vector2f topLeftCage = { rect.left / cageSize, rect.top / cageSize };
	const sf::Vector2f bottomRightCage = { (rect.left + rect.width) / cageSize, (rect.top + rect.height) / cageSize };
	
	CollisionInfo result = singleCollisionY(topLeftCage.x, bottomRightCage.x, map, bottomRightCage.y, cageSize);

	if (result.collisionSide != 0)
	{
		return result;
	}
	
	result = singleCollisionY(topLeftCage.x, bottomRightCage.x, map, topLeftCage.y, cageSize);
	
	return result;
}

CollisionInfo Player::singleCollisionY(const float left, const float right, const Map& map, const int y, const int& cageSize) const
{
	CollisionInfo result;
	
	// left
	for (int x = left; x < right; x++)
	{
		const int curCage = map.getCage(sf::Vector2i(x, y));

		// Collision check
		if (isBlock(curCage))
		{
			if (plVelocity.y > 0)
			{
				result.collisionSide = -1;
				result.availablePos = y * cageSize - rect.height;	
			}
			else if(plVelocity.y < 0)
			{
				result.collisionSide = 1;
				result.availablePos = (y + 1) * cageSize;
			}
		}
	}
	return result;
}

CollisionInfo Player::bottomStairsCollisionY(const Map& map) const
{
	const int cageSize = map.getCageSize();
	const float left = rect.left / cageSize;
	const float right = (rect.left + rect.width) / cageSize;
	const int bottom =  (rect.top + rect.height) / cageSize ;
	
	// Checking is player staying on top of the stair
	CollisionInfo result;

	for (int x = left; x < right; x++)
	{
		const int curCage = map.getCage(sf::Vector2i(x, bottom));
		if (isTopOfStairs(curCage))
		{
			result.collisionSide = -1;
			result.availablePos = bottom * cageSize - rect.height;
		}
	}

	return result;
}

bool Player::isStairs(const int curCage)
{
	return (curCage == 3) || (curCage == 4);
}

bool Player::isTopOfStairs(const int curCage)
{
	return (curCage == 4);
}

bool Player::isBlock(const int curCage)
{
	return curCage != -1 && !isStairs(curCage);
}

void Player::jump()
{
	plVelocity.y = -defVel.y;
	onGround = false;
}

void Player::move(const int direction)
{
	// Directions: 1 - left, -1 - right
	plVelocity.x = direction * -defVel.x;
}

void Player::grabOnStairs(const int direction)
{
	plVelocity.y = direction * -defVel.y / 2;
}

void Player::setPos(const sf::Vector2f pos)
{
	rect.left = pos.x - rect.width / 2;
	rect.top = pos.y - rect.height;
}

sf::Vector2i Player::getPos() const
{
	sf::Vector2i pos;
	
	pos.x = rect.left + rect.width / 2;
	pos.y = rect.top + rect.height;

	return pos;
}

bool Player::isOnGround() const
{
	return onGround;
}

bool Player::isStairsAvailable() const
{
	return stairsAvailable;
}


bool Player::isOnStairs() const
{
	return isNowOnStairs;
}

sf::Sprite Player::getSprite(const sf::Vector2i offset) const
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(rect.left - offset.x, rect.top - offset.y));
	
	return playerSprite;
}

sf::RectangleShape Player::dbgSprite(const sf::Vector2i offset) const
{
	sf::RectangleShape dbg;
	const int cageSize = 32;
	const int thick = 4;
	dbg.setPosition(sf::Vector2f(cageSize * (rect.left / cageSize) - offset.x + thick, cageSize * (rect.top / cageSize) - offset.y + thick));

	dbg.setSize(sf::Vector2f(rect.width - thick * 2, rect.height - thick * 2));
	dbg.setOutlineThickness(thick);
	if(stairsAvailable)
	{
		dbg.setOutlineColor(sf::Color::Red);
	}
	else
	{
		dbg.setOutlineColor(sf::Color::Cyan);
	}
	
	return dbg;
}