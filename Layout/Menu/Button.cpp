#include "Button.h"

Button::Button(sf::Vector2i position, sf::Vector2i size) : _position(position), _size(size)
{
	_texture.create(_size.x, _size.y);
	_passiveColor = sf::Color(0,0,255);
	_activeColor = sf::Color(120,0,255);
	
	_font.loadFromFile("arial.ttf");
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

bool Button::isClicked()
{
	return _isClicked;
}

bool Button::isActive()
{
	return _isActive;
}

sf::Sprite Button::getSprite()
{
	auto rect = sf::RectangleShape(sf::Vector2f(_size));

	sf::Text text;
	
	text.setFont(_font);
	text.setStyle(sf::Text::Bold);
	text.setString(_btnText);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);

	if(_isActive)
	{
		rect.setFillColor(_activeColor);
	}
	else
	{
		rect.setFillColor(_passiveColor);
	}

	_texture.clear();

	_texture.draw(rect);
	_texture.draw(text);

	_texture.display();

	auto sprite = sf::Sprite(_texture.getTexture());
	sprite.setPosition(_position.x, _position.y);

	return sprite;
}

void Button::setText(const std::string& text)
{
	_btnText = text;
}
