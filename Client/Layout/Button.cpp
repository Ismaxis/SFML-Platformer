#include "Button.h"

#include <iostream>

Button::Button(sf::Vector2i position, sf::Vector2i size) : _position(position), _size(size) {
}

Button::~Button() {
}

void Button::setTexture(const std::string& defTexturePath, const std::string& activeTexturePath) {
    if (!defTexture.loadFromFile(defTexturePath)) {
        std::cout << "Could not open default button texture" << std::endl;
    } else {
        const sf::Vector2i originalSize(defTexture.getSize());
        defSprite.setTexture(defTexture);
        defSprite.setScale(_size.x / originalSize.x, _size.y / originalSize.y);
        defSprite.setPosition(_position.x, _position.y);
    }

    if (!actTexture.loadFromFile(activeTexturePath)) {
        std::cout << "Could not open active button texture" << std::endl;
    } else {
        const sf::Vector2i originalSize(actTexture.getSize());
        actSprite.setTexture(actTexture);
        actSprite.setScale(_size.x / originalSize.x, _size.y / originalSize.y);
        actSprite.setPosition(_position.x, _position.y);
    }
}

void Button::update(sf::Vector2i mousePos, bool lmb) {
    if (mousePos.x > _position.x && mousePos.x < _position.x + _size.x) {
        if (mousePos.y > _position.y && mousePos.y < _position.y + _size.y) {
            if (lmb) {
                _isClicked = true;
                _isActive = true;
                return;
            } else {
                _isActive = true;
                return;
            }
        }
    }
    _isActive = false;
    _isClicked = false;
}

bool Button::isClicked() const {
    return _isClicked;
}

bool Button::isActive() const {
    return _isActive;
}

sf::Sprite* Button::getSprite() {
    if (isActive()) {
        return &actSprite;
    } else {
        return &defSprite;
    }
}
