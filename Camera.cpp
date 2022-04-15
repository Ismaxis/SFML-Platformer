#include "Camera.h"

Camera::Camera()
{
	offset = sf::Vector2i(0,0);
	camAcceleration = sf::Vector2f(0,0);
	camVelocity = sf::Vector2f(0,0);
}

sf::Vector2i Camera::calculateOffsets(sf::Vector2i playerPos, sf::Vector2f playerVel, sf::Vector2u winPixelSize, sf::Vector2u mapPixelSize)
{
	// X offset
	camAcceleration.x = 0;

	if (offset.x < playerPos.x - winPixelSize.x * 0.8)
	{
		offset.x = playerPos.x - winPixelSize.x * 0.8;
	}
	if (offset.x > abs(playerPos.x - winPixelSize.x * 0.15))
	{
		offset.x = playerPos.x - winPixelSize.x * 0.15;
	}
	if (offset.x <= playerPos.x - winPixelSize.x * 0.49 && offset.x >= playerPos.x - winPixelSize.x * 0.51)
	{
		camAcceleration.x = 0;
		camVelocity.x = 0;
	}
	if (offset.x < playerPos.x - winPixelSize.x * 0.5 && playerVel.x == 0)
	{
		camAcceleration.x = (playerPos.x - winPixelSize.x * 0.5)/10000.0;
	}
	if (offset.x > abs(playerPos.x - winPixelSize.x * 0.5) && playerVel.x == 0)
	{
		camAcceleration.x = -(playerPos.x - winPixelSize.x * 0.5)/10000.0;
	}

	camVelocity.x += camAcceleration.x;
	offset.x += camVelocity.x;

	if(offset.x < 0)
	{
		camAcceleration.x = 0;
		camVelocity.x = 0;
		offset.x = 0;
	}
	if(offset.x > mapPixelSize.x - winPixelSize.x)
	{
		camAcceleration.x = 0;
		camVelocity.x = 0;
		offset.x = mapPixelSize.x - winPixelSize.x;
	}



	// Y offset
	if (playerPos.y > mapPixelSize.y - winPixelSize.y / 2u)
	{
		offset.y = mapPixelSize.y - winPixelSize.y;
	}
	else if (playerPos.y > winPixelSize.y / 2u)
	{
		offset.y = playerPos.y - winPixelSize.y / 2u;
	}
	else
	{
		offset.y = 0;
	}

	return offset;
}
