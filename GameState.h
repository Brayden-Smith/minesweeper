#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "Tile.h"
class Tile;
#include <time.h>

class GameState
{
public:
    enum PlayStatus { WIN, LOSS, PLAYING};
private:
    sf::Vector2i dimensions;
    int numberofmines;
    std::vector<std::vector<Tile>> tiles;
    PlayStatus status;
    std::array<Tile*, 8> neighbors;
public:
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25,16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    sf::Vector2i getDimensions();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
};