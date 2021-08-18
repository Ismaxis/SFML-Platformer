#include "Player.h"

void Player::update(const Map map, const int time)
{
	// X
	rect.left += plVelocity.x * time;
	collision(map, 0);

	// Y
	plVelocity.y += time * 0.008f;
	
	rect.top += plVelocity.y * time;
	onGround = false;
	collision(map, 1);

	plVelocity.x = 0;
}

void Player::collision(Map map, const int mode)
// Mode: 0 - x check, 1 - y check
{
	const int cageSize = map.getCageSize();
	for (int x = rect.left / cageSize; x < (rect.left + rect.width) / cageSize; x++)
	{
		for (int y = rect.top / cageSize; y < (rect.top + rect.height) / cageSize; y++)
		{
			const int curCage = map.getCage(sf::Vector2i(x, y));
			if (curCage != -1)
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

void Player::move(const int direction)
// Directions: -1 - left, 1 - right
{
	plVelocity.x = direction * defVel.x;
}

void Player::jump()
{
	plVelocity.y = -defVel.y;
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

bool Player::getStatus() const
{
	return onGround;
}

sf::Vector2u Player::getSize() const
{
	return sf::Vector2u(rect.width, rect.height);
}

sf::Sprite Player::getSprite(const sf::Vector2i offset) const
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(rect.left - offset.x, rect.top - offset.y));
	
	return playerSprite;
}