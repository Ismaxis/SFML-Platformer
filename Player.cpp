#include "Player.h"

void Player::update()
{
	plPosition.x += plVelocity.x;
	plPosition.y -= plVelocity.y;
}

void Player::setPos(sf::Vector2f pos)
{
	plPosition.x = pos.x - plSize.x / 2;
	plPosition.y = pos.y - plSize.y;
}

void Player::setVel(sf::Vector2f vel)
{
	plVelocity.x = vel.x;
	plVelocity.y = vel.y;
}

sf::Vector2f Player::getPos()
{
	// Bottom point
	sf::Vector2f pos;
	
	pos.x = plPosition.x + plSize.x / 2;
	pos.y = plPosition.y + plSize.y;

	return pos;
}

sf::Vector2f Player::getVel()
{
	return plVelocity;
}

sf::Vector2u Player::getSize()
{
	return plSize;
}

sf::Sprite Player::getSprite()
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(plPosition));
	
	return playerSprite;
}