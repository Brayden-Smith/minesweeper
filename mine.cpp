#include "mine.h"

Mine::Mine(sf::Vector2f _position, bool actualMine) {
    sprite.setPosition(_position);
    //makes it invisible
    sprite.setColor(sf::Color(255,255,255,0));
    exists = actualMine;

    //only needs a texture if it exists
    if (exists) {
        mineTexture.loadFromFile("images/mine.png");
        sprite.setTexture(mineTexture);
    }
}

Mine::Mine() {
    sprite.setPosition(0,0);
    exists = false;
}

sf::Vector2f Mine::getLocation() {
    return sprite.getPosition();
}

sf::Color Mine::getColor() {
    return sprite.getColor();
}

void Mine::setColor(sf::Color color) {
    sprite.setColor(color);
}

//overload assignment operator
void Mine::operator=(Mine& m) {
    //sets the variable to the pass
    sprite.setPosition(m.getLocation());
    sprite.setColor(m.getColor());
    exists = m.doesExist();

    //if it is supposed to exit it sets the texture to mine.png
    if (exists) {
        mineTexture.loadFromFile("images/mine.png");
        sprite.setTexture(mineTexture);
    }
}

sf::Sprite* Mine::getSprite() {
    return &sprite;
}

bool Mine::doesExist() {
    return exists;
}
