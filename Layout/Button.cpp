#include "Button.h"

#include <iostream>

Button::Button(sf::Vector2i position, sf::Vector2i size) : _position(position), _size(size)
{
	_texture.create(_size.x, _size.y);
}

void Button::setTexture(const std::string& defTexturePath, const std::string& activeTexturePath)
{
	if(!_defTexture.loadFromFile(defTexturePath))
	{
		std::cout << "Could not open default button texture" << std::endl;
	}
	if(!_actTexture.loadFromFile(activeTexturePath))
	{
		std::cout << "Could not open active button texture" << std::endl;
	}

	_originalTextureSize = _defTexture.getSize(); // if _defTexture.getSize() = _actTexture.getSize()
}

void Button::update(sf::Vector2i mousePos, bool lmb)
{
	if(mousePos.x > _position.x && mousePos.x < _position.x + _size.x)
	{
		if(mousePos.y > _position.y && mousePos.y < _position.y + _size.y)
		{
			if(lmb)
			{
				_isClicked = true;
				_isActive = true;
				return;
			}
			else
			{
				_isActive = true;
				return;
			}
		}
	}
	_isActive = false;
	_isClicked = false;
}

bool Button::isClicked() const
{
	return _isClicked;
}

bool Button::isActive() const
{
	return _isActive;
}

sf::Sprite Button::getSprite()
{
	sf::Sprite btnSprite;
	if(isActive())
	{
		btnSprite.setTexture(_actTexture);
	}
	else
	{
		btnSprite.setTexture(_defTexture);
	}
	btnSprite.setScale(_size.x/_originalTextureSize.x, _size.y/_originalTextureSize.y);

	_texture.clear(sf::Color(0,0,0,0));
	_texture.draw(btnSprite);
	_texture.display();

	auto resultSprite = sf::Sprite(_texture.getTexture());
	resultSprite.setPosition(_position.x, _position.y);

	return resultSprite;
}