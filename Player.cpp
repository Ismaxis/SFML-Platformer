#include "Player.h"

void Player::update(const Map &map, int time)
{
	// time check
	if (time > 10)
	{
		time = 10;
	}
	// X
	rect.left += plVelocity.x * time;
	const CollisionInfo hCol = collision(map, 0);

	// todo разобраться структурой, которую буду возвращать. Подоробнее в gNotes
	
	if (hCol.collisionSide == -1)
	{
		rect.left = hCol.availablePos;
	}
	else if(hCol.collisionSide == 1)
	{
		rect.left = hCol.availablePos;
	}
	
	// Y
	if (!onStairs)
	{
		plVelocity.y += time * 0.008f;
	}

	rect.top += plVelocity.y * time;

	onStairs = false;
	onGround = false;
	
	const CollisionInfo vCol = collision(map, 1);

	if (vCol.collisionSide == -1)
	{
		rect.top = vCol.availablePos;
		plVelocity.y = 0;
		onGround = true;
	}
	else if (vCol.collisionSide == 1)
	{
		rect.top = vCol.availablePos;
		plVelocity.y = 0;
	}
	
	plVelocity.x = 0;
}

// Return: 0 - no collision at axis, 1 left/top, -1 - right/bottom
CollisionInfo Player::collision(const Map &map, const int mode)
// Mode: 0 - x check, 1 - y check
{
	const int cageSize = map.getCageSize();

	const sf::Vector2f topLeftCage{ rect.left / cageSize, rect.top / cageSize };
	const sf::Vector2f bottomRightCage{ (rect.left + rect.width) / cageSize, (rect.top + rect.height) / cageSize };

	CollisionInfo result;
	
	// All cages occupied by player check
	for (int x = topLeftCage.x; x < bottomRightCage.x; x++)
	{
		for (int y = topLeftCage.y; y < bottomRightCage.y; y++)
		{
			const int curCage = map.getCage(sf::Vector2i(x, y));
			// Stairs check
			if (curCage == 3)
			{
				onStairs = true;
			}
			
			// Collision check
			else if (curCage != -1) 
			{
				// X
				if (mode == 0)
				{
					// right
					if (plVelocity.x > 0)
					{
						result.collisionSide = -1;
						result.availablePos = x * cageSize - rect.width;
					}
					// left
					else if (plVelocity.x < 0)
					{
						result.collisionSide = 1;
						result.availablePos = (x + 1) * cageSize;
					}
				}

				// Y
				else if (mode == 1)
				{
					// bottom
					if (plVelocity.y > 0)
					{
						result.collisionSide = -1;
						result.availablePos = y * cageSize - rect.height;
					}
					// top
					else if (plVelocity.y < 0)
					{
						result.collisionSide = 1;
						result.availablePos = (y + 1) * cageSize;
					}
				}
			}
		}
	}
	return result;
}

void Player::jump()
{
	plVelocity.y = -defVel.y;
	onGround = false;
}

void Player::move(const int direction)
{
	// Directions: -1 - left, 1 - right
	plVelocity.x = direction * defVel.x;
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

bool Player::isOnStairs() const
{
	return onStairs;
}

sf::Sprite Player::getSprite(const sf::Vector2i offset) const
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(rect.left - offset.x, rect.top - offset.y));
	
	return playerSprite;
}