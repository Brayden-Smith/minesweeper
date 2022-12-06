#pragma once
#include <SFML/Graphics.hpp>

class Mine
{
    sf::Sprite sprite;
    sf::Texture mineTexture;
    bool exists;

public:
    Mine(sf::Vector2f _position, bool actualMine);
    Mine();
    sf::Vector2f getLocation();
    sf::Color getColor();
    void setColor(sf::Color color);
    void operator=(Mine& m);
    sf::Sprite* getSprite();
    bool doesExist();
};
