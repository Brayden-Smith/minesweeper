#include "Button.h"


//constructor with position and onclick function
Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {

    sprite.setPosition(_position);
    click = _onClick;

}

//returns the position of the button
sf::Vector2f Button::getPosition() {
    return sprite.getPosition();
}

//returns the current sprite of the button
sf::Sprite* Button::getSprite() {
    return &sprite;
}


//sets this buttons visualization to the sprite
void Button::setSprite(sf::Sprite* _sprite) {
    buttonTexture = *_sprite->getTexture();
    sprite.setTexture(buttonTexture);
}

//invokes the buttons callback method
void Button::onClick() {
    click();
}