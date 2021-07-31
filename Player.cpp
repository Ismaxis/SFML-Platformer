#include "Player.h"

void Player::update(Map map, float time)
{
	// X
	Rect.left += plVelocity.x * time;
	Collision(map, 0);

	// Y
	plVelocity.y += time * 0.006;
	
	Rect.top += plVelocity.y * time;
	onGround = false;
	Collision(map, 1);

	plVelocity.x = 0;
}

void Player::Collision(Map map, int mode)
// Mode: 0 - x check, 1 - y check
{
	int cageSize = map.getCageSize();
	for (size_t x = Rect.left / cageSize; x < (Rect.left + Rect.width) / cageSize; x++)
	{
		for (size_t y = Rect.top / cageSize; y < (Rect.top + Rect.height) / cageSize; y++)
		{
			int curCage = map.getCage(sf::Vector2i(x, y));
			if (curCage != -1)
			{
				// X
				if (mode == 0)
				{
					if (plVelocity.x > 0)
					{
						Rect.left = x * cageSize - Rect.width;
					}
					else if (plVelocity.x < 0)
					{
						Rect.left = (x + 1) * cageSize;
					}
				}

				// Y
				else if (mode == 1)
				{
					if (plVelocity.y > 0)
					{
						Rect.top = y * cageSize - Rect.height;
						plVelocity.y = 0;
						onGround = true;
					}
					else if (plVelocity.y < 0)
					{
						Rect.top = (y + 1) * cageSize;
						plVelocity.y = 0;
					}
				}
			}
		}
	}
}

void Player::Move(int direction)
// Directions: -1 - left, 1 - right
{
	plVelocity.x = direction * defVel.x;
}

void Player::Jump()
{
	plVelocity.y = -defVel.y;
}

void Player::setPos(sf::Vector2f pos)
{
	Rect.left = pos.x - Rect.width / 2;
	Rect.top = pos.y - Rect.height;
}

sf::Vector2f Player::getPos()
{
	sf::Vector2f pos;
	
	pos.x = Rect.left + Rect.width / 2;
	pos.y = Rect.top + Rect.height;

	return pos;
}

bool Player::getStatus()
{
	return onGround;
}

sf::Vector2u Player::getSize()
{
	return sf::Vector2u(Rect.width, Rect.height);
}

sf::Sprite Player::getSprite()
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(Rect.left, Rect.top));
	
	return playerSprite;
}