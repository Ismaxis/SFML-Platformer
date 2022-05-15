#pragma once
#include <SFML/Graphics.hpp>
class Button
{

public:
	Button(sf::Vector2i position, sf::Vector2i size);

	~Button();

	void setTexture(const std::string& defTexturePath, const std::string& activeTexturePath);

	void update(sf::Vector2i mousePos, bool lmb);
	bool isClicked() const;
	bool isActive() const;
	sf::Sprite getSprite();

private:
	bool _isClicked;
	bool _isActive;

	sf::Vector2i _position; // top left corner 
	sf::Vector2i _size;

	sf::RenderTexture _texture; // todo remove this

	sf::Texture _defTexture;
	sf::Sprite defSprite;
	sf::Texture _actTexture;
	sf::Sprite actSprite;
	sf::Vector2u _originalTextureSize;
};