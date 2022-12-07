#include "Tile.h"

//constructs it not much going on here
Tile::Tile(sf::Vector2f position) {
    sprite.setPosition(position);
    flag.setPosition(position);

    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);

    state = HIDDEN;
}

//default constructor
Tile::Tile() {
    sprite.setPosition(sf::Vector2f(0,0));
    flag.setPosition(sf::Vector2f(0,0));
    state = HIDDEN;
}

//returns the position of the tile
sf::Vector2f Tile::getLocation() {
    return sprite.getPosition();
}

//returns state of the tile
Tile::State Tile::getState() {
    return state;
}

//changes the state and texture to the state that is passed in
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

//returns the neighbors of the tile
std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}

//sets the neighbors variable to whats passed in
void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
        neighbors = _neighbors;
}

//the logic what happens when a tile is right clicked
void Tile::onClickRight() {
    //if its hidden it sets to flagged and vice versa
    if (state == HIDDEN) {
        this->setState(Tile::State (2));
    }
    else if (state == FLAGGED) {
        this->setState(Tile::State (1));
    }
}

//the logic that happens when a tile is left clicked
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
            //reveals the number underneath then reveals neighbors if there are no near mines
            this->setState(REVEALED);
            toolbox.mines[sprite.getPosition().x /32][sprite.getPosition().y /32].setColor(sf::Color(255,255,255,255));
            if (toolbox.mines[sprite.getPosition().x /32][sprite.getPosition().y /32].getNearMines() == 0)
            {
                this->revealNeighbors();
            }
        }
    }
}

//renders the tile and flag if it is toggled
void Tile::draw() {
    Toolbox& Toolbox = Toolbox::getInstance();
    Toolbox.window.draw(sprite);
    if (flagToggle) {
        Toolbox.window.draw(flag);
    }
}

//copy constructor :(
Tile::Tile(Tile& t) {
    sprite.setPosition(t.getLocation());
    flag.setPosition(sprite.getPosition());

    state = t.getState();
    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);
}

//assignment operator overloader
Tile& Tile::operator=(Tile &t) {
    sprite.setPosition(t.getLocation());
    flag.setPosition(sprite.getPosition());

    state = t.getState();
    texture.loadFromFile("images/tile_hidden.png");
    sprite.setTexture(texture);

    flagTexture.loadFromFile("images/flag.png");
    flag.setTexture(flagTexture);

    this->setState(t.getState());
    return *this;
}

//makes sure that they are hidden and don
void Tile::revealNeighbors() {
    Toolbox& toolbox = Toolbox::getInstance();
    //checks adjacent tiles to see if they are hidden and dont have a bomb
    for(int i = 0; i < 8; i++)
    {
        if (neighbors[i] != nullptr && neighbors[i]->getState() == HIDDEN)
        {
            if (!toolbox.mines[neighbors[i]->getLocation().x / 32][neighbors[i]->getLocation().y / 32].doesExist())
            {
                neighbors[i]->onClickLeft();
            }
        }
    }
}