#pragma once
#include<SFML/Graphics.hpp>

// Offset Generator  
class Camera
{
public:
	Camera();
	sf::Vector2i calculateOffsets(sf::Vector2i playerPos, sf::Vector2f playerVel, sf::Vector2u winPixelSize, sf::Vector2u mapPixelSize); 

private:
	sf::Vector2i offset;
	sf::Vector2f camAcceleration;
	sf::Vector2f camVelocity;
};