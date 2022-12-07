#include "mine.h"

Mine::Mine(sf::Vector2f _position, bool actualMine) {
    sprite.setPosition(_position);
    //makes it invisible
    sprite.setColor(sf::Color(255,255,255,0));
    exists = actualMine;
    isDrawn = false;
    //only needs a texture if it exists
    if (exists) {
        mineTexture.loadFromFile("images/mine.png");
        sprite.setTexture(mineTexture);
        isDrawn = true;
    }
}

Mine::Mine() {
    sprite.setPosition(0,0);
    exists = false;
    isDrawn = false;
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
    nearMines = m.getNearMines();
    neighbors = m.neighbors;
    isDrawn = m.isDrawn;

    //if it is supposed to exit it sets the texture to mine.png
    if (exists)
    {
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

void Mine::setNeighbors(std::array<Mine*, 8> _neighbors) {
    neighbors = _neighbors;

    if (!this->doesExist())
    {
        //counts the number of nearby mines
        nearMines = 0;
        for(int i = 0; i < 8; i ++) {
            if (neighbors[i] != nullptr) {
                if(neighbors[i]->doesExist()) {
                    nearMines++;
                }
            }
        }

        if(nearMines != 0)
        {
            //leads in the correct file number then sets the sprite to look like it
            isDrawn = true;
            mineTexture.loadFromFile("images/number_" + std::to_string(nearMines) + ".png");
            sprite.setTexture(mineTexture);
        }
    }
}

int Mine::getNearMines() {
    return nearMines;
}
