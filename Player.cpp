#include "Player.h"

void Player::init(sf::Vector2i pos, std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cout << "Hyi" << std::endl;
	}

	plTexture = texture;

	plSize = texture.getSize();

	plPosition.x = pos.x - plSize.x / 2;
	plPosition.y = pos.y - plSize.y;
}

void Player::update(sf::Vector2f vel)
{
	plVelocity = vel;

	plPosition.x += plVelocity.x;
	plPosition.y -= plVelocity.y;
}

void Player::setPos(sf::Vector2i pos)
{
	plPosition.x = pos.x - plSize.x / 2;
	plPosition.y = pos.y - plSize.y;
}

sf::Vector2i Player::getPos()
{
	// Bottom point
	sf::Vector2i pos;
	
	pos.x = plPosition.x + plSize.x / 2;
	pos.y = plPosition.y + plSize.y;

	return pos;
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