#include "Player.h"

void Player::update(const Map &map, const int time)
{
	// X
	rect.left += plVelocity.x * time;
	collision(map, 0);

	// Y

	plVelocity.y += time * 0.008f;
	rect.top += plVelocity.y * time;
	
	onStairs = false;
	onGround = false;
	collision(map, 1);

	plVelocity.x = 0;
}

void Player::collision(const Map &map, const int mode)
// Mode: 0 - x check, 1 - y check
{
	const int cageSize = map.getCageSize();

	sf::Vector2f topLeftCage = { rect.left / cageSize, rect.top / cageSize };
	sf::Vector2f bottomRightCage = { (rect.left + rect.width) / cageSize, (rect.top + rect.height) / cageSize };

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
					if (plVelocity.x > 0)
					{
						rect.left = x * cageSize - rect.width;
					}
					else if (plVelocity.x < 0)
					{
						rect.left = (x + 1) * cageSize;
					}
				}

				// Y
				else if (mode == 1)
				{
					if (plVelocity.y > 0)
					{
						rect.top = y * cageSize - rect.height;
						plVelocity.y = 0;
						onGround = true;
					}
					else if (plVelocity.y < 0)
					{
						rect.top = (y + 1) * cageSize;
						plVelocity.y = 0;
					}
				}
			}
		}
	}
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
	if (direction != 0)
	{
		plVelocity.y = direction * -defVel.y;
	}
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