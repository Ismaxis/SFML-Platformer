#include "Camera.h"
#include <iostream>

Camera::Camera(const sf::Vector2u& winPixelSize, const sf::Vector2u& mapPixelSize) : winPixelSize(winPixelSize), mapPixelSize(mapPixelSize)
{
	offset = sf::Vector2i(0,0);
	camAcceleration = sf::Vector2f(0,0);
	camVelocity = sf::Vector2f(0,0);
}

sf::Vector2i Camera::calculateOffsets(const sf::Vector2i& playerPos, const sf::Vector2f& playerVel)
{
	// X offset
	camAcceleration.x = 0;

	// follow when close to border
	const float distFromPlayerToBorder = playerPos.x - offset.x - winPixelSize.x * distanceToBorder;
	if (distFromPlayerToBorder - winPixelSize.x * (1.f - 2.f * distanceToBorder) > 0)
	{
		offset.x = playerPos.x - winPixelSize.x * (1.f - distanceToBorder);
	}
	if (distFromPlayerToBorder < 0)
	{
		offset.x = playerPos.x - winPixelSize.x * distanceToBorder;
	}

	// center cam when don't move
	const float delta = playerPos.x - (offset.x + winPixelSize.x * 0.5f);
	if (abs(delta) < winPixelSize.x * 0.01f)
	{
		camAcceleration.x = 0.f;
		camVelocity.x = 0.f;
	}
	else if (delta > 0.f && playerVel.x == 0.0f)
	{
		camAcceleration.x = delta/magicDivider;
	}
	else if (delta < 0.f && playerVel.x == 0.f)
	{
		camAcceleration.x = delta/magicDivider;
	}

	camVelocity.x += camAcceleration.x;
	offset.x += camVelocity.x;

	// don't let camera go out of world
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
