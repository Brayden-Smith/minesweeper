#include "Toolbox.h"




void test1Click() {
    std::cout<< 3;
}

void test2Click() {
    std::cout<< 4;
}

Button debug(sf::Vector2f(496 ,512), toggleDebugMode);

Button newGame(sf::Vector2f(368 ,512), restart);

Button test1(sf::Vector2f(560 ,512), test1Click);

Button test2(sf::Vector2f(624,512), test2Click);

GameState game;

Toolbox::Toolbox() {
   gameState = &game;

    sf::RenderWindow window(sf::VideoMode(800,600), "P4 - Minesweeper, <Brayden Smith>");
    debugMode = false;


    sf::Texture texture;
    sf::Sprite sprite;


    //creates the debug button
        //gets the sprite from file
        texture.loadFromFile("images/debug.png");
        sprite.setTexture(texture);

        //sets the sprite and button pointer
        debug.setSprite(&sprite);
        debugButton = &debug;
        buttons[0] = debugButton;

    //creates the newGame button
        //gets the sprite from file
        texture.loadFromFile("images/face_happy.png");
        sprite.setTexture(texture);

        newGame.setSprite(&sprite);
        newGameButton = &newGame;
        buttons[1] = newGameButton;

    //creates the test1 button
        //gets the sprite from file
        texture.loadFromFile("images/test_1.png");
        sprite.setTexture(texture);

        test1.setSprite(&sprite);
        testButton1 = &test1;
        buttons[2] = testButton1;

    //creates the test2 button
        //gets the sprite from file
        texture.loadFromFile("images/test_2.png");
        sprite.setTexture(texture);

        test2.setSprite(&sprite);
        testButton2 = &test2;
        buttons[3] = testButton2;


}


//creates the toolbox instance and returns its reference
Toolbox &Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}


void Toolbox::createBoard(std::vector<std::vector<int>> _board) {
    board = _board;
    for (int j = 0; j < board.size(); j++) {
        for(int i = 0; i < board[j].size(); i ++) {
            if (board[j][i] == 1)
            {
                Mine mine(sf::Vector2f(32 * j, 32 * i), true);
                mines[j][i] = mine;
            }
            else {
                Mine mine(sf::Vector2f(32 * j, 32 * i), false);
                mines[j][i] = mine;
            }
        }
    }
}


