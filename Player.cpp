#include "Player.h"
#include "PlayerInfo.h"

void Player::update()
{
	position.x += velocity.x;
	position.y -= velocity.y;
}
PlayerInfo Player::getInfo()
{
	PlayerInfo info;
	info.position = position;
	info.size = size;
	info.texture = texture;

	return info;
}

sf::Sprite* Player::draw(sf::Vector2u winSize)
{
	sf::Sprite playerSprite;

	playerSprite = 
}