#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include "minesweeper.h"
#include "GameState.h"
#include <iostream>
#include "mine.h"
class GameState;

class Toolbox
{

    Toolbox();
    std::vector<std::vector<int>> board;
    std::array<Mine*, 8> neighbors;
    sf::Texture digits;

public:
    sf::RenderWindow window;
    GameState* gameState;
    Button* buttons[4];
    Button* debugButton;
    Button* newGameButton;
    sf::Texture newGameTexture;
    Button* testButton1;
    Button* testButton2;
    bool debugMode = false;
    static Toolbox& getInstance();
    void createBoard(std::vector<std::vector<int>> _board);
    std::array<std::array<Mine,16>, 25> mines;
    void setMineNeighbors();

    std::array<sf::Sprite*, 4> getCounter();
    sf::Sprite counterSign;
    sf::Sprite digit1;
    sf::Sprite digit2;
    sf::Sprite digit3;
};
