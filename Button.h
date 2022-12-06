#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
    sf::Sprite sprite;
    std::function<void(void)> click;
    sf::Texture buttonTexture;
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};