#pragma once
#include <SFML/Graphics.hpp>
#include "Toolbox.h"

class Tile
{
public:
    enum State {REVEALED, HIDDEN, FLAGGED, EXPLODED};

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderTexture renderTexture;
    std::array<Tile*, 8> neighbors;
    sf::Sprite flag;
    sf::Texture flagTexture;
    bool flagToggle;
    State state;

public:
    Tile(sf::Vector2f position);
    Tile();
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
    Tile(Tile& t);
    Tile& operator= (Tile& t);


protected:
    void revealNeighbors();
};