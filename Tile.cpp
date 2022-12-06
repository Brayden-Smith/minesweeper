#include "Tile.h"

Tile::Tile(sf::Vector2f position) {
    sprite.setPosition(position);
    flag.setPosition(position);

    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);

    state = HIDDEN;
}

Tile::Tile() {
    sprite.setPosition(sf::Vector2f(0,0));
    flag.setPosition(sf::Vector2f(0,0));
    state = HIDDEN;
}

sf::Vector2f Tile::getLocation() {
    return sprite.getPosition();
}

Tile::State Tile::getState() {
    return state;
}

void Tile::setState(Tile::State _state) {
    state = _state;

    switch (state)
    {
        case 0:
            texture.loadFromFile("images/tile_revealed.png");
            sprite.setTexture(texture);
            flagToggle = false;
            break;
        case 1:
            texture.loadFromFile("images/tile_hidden.png");
            sprite.setTexture(texture);
            flagToggle = false;
            break;
        case 2:
            texture.loadFromFile("images/tile_hidden.png");
            sprite.setTexture(texture);
            flagToggle = true;
            break;
        case 3:
            texture.loadFromFile("images/tile_revealed.png");
            sprite.setTexture(texture);
            flagToggle = false;
            lost();
    }
}

std::array<Tile*, 8> neighbors;

std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}

void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {

}

void Tile::onClickRight() {
    if (state == HIDDEN) {
        this->setState(Tile::State (2));
    }
    else if (state == FLAGGED) {
        this->setState(Tile::State (1));
    }
}

void Tile::onClickLeft() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (state == HIDDEN)
    {
        //if the mine at this location exists then it goes into exploded state
        if (toolbox.mines[sprite.getPosition().x /32][sprite.getPosition().y /32].doesExist()) {
            this->setState(EXPLODED);
            toolbox.mines[sprite.getPosition().x /32][sprite.getPosition().y /32].setColor(sf::Color(255,255,255,255));
        }
        else
        {
            this->setState(REVEALED);
        }
    }
}

void Tile::draw() {
    Toolbox& Toolbox = Toolbox::getInstance();
    Toolbox.window.draw(sprite);
    if (flagToggle) {
        Toolbox.window.draw(flag);
    }
}

Tile::Tile(Tile& t) {
    sprite.setPosition(t.getLocation());
    flag.setPosition(sprite.getPosition());

    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);
}

Tile& Tile::operator=(Tile &t) {
    sprite.setPosition(t.getLocation());
    flag.setPosition(sprite.getPosition());

    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);

    this->setState(t.getState());
    return *this;
}