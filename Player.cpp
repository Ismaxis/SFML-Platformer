#include<iostream>
#include "Player.h"
#include "PlayerInfo.h"

void Player::update(sf::Vector2f vel)
{
	plVelocity = vel;

	plPosition.x += plVelocity.x;
	plPosition.y -= plVelocity.y;
}

void Player::setPos(sf::Vector2i pos)
{
	plPosition = pos;
}

sf::Vector2i Player::getPos()
{
	sf::Vector2i pos;
	
	pos.x = plPosition.x;
	pos.y = plPosition.y + plSize.y;

	return plPosition;
}

PlayerInfo Player::getInfo()
{
	PlayerInfo info;
	info.position = plPosition;
	info.size = plSize;
	info.texture = plTexture;

	return info;
}

void Player::init(sf::Vector2i pos, sf::Texture texture)
{
	plTexture = texture;

	plSize = texture.getSize();

	plPosition.x = pos.x - plSize.x / 2;
	plPosition.y = pos.y - plSize.y;
}

sf::Sprite Player::getSprite()
{
	sf::Sprite playerSprite;
	
	playerSprite.setTexture(plTexture);
	playerSprite.setPosition(sf::Vector2f(plPosition));
	

	return playerSprite;
}