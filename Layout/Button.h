#pragma once
#include <SFML/Graphics.hpp>
class Button
{

public:
	Button(sf::Vector2i position, sf::Vector2i size);

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

	sf::RenderTexture _texture;

	sf::Font _font;
	std::string _btnText;

	sf::Texture _defTexture;
	sf::Texture _actTexture;
	sf::Vector2u _originalTextureSize;

};