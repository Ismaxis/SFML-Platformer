#pragma once
#include<SFML/Graphics.hpp>

// Offset Generator  
class Camera
{
public:
	Camera(const sf::Vector2u& winPixelSize, const sf::Vector2u& mapPixelSize);
	sf::Vector2i calculateOffsets(const sf::Vector2i& playerPos, const sf::Vector2f& playerVel); 

private:
    const float magicDivider = 4500.0f;
    const float distanceToBorder = 0.4f; // % of screen width

	sf::Vector2u winPixelSize;
	sf::Vector2u mapPixelSize;

	sf::Vector2i offset;
	sf::Vector2f camAcceleration;
	sf::Vector2f camVelocity;
};