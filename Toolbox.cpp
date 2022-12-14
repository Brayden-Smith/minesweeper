#include "Toolbox.h"




void test1Click() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState->setPlayStatus(GameState::LOSS);
}

void test2Click() {
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gameState->setPlayStatus(GameState::PLAYING);
}

Button debug(sf::Vector2f(496 ,512), toggleDebugMode);

Button newGame(sf::Vector2f(368 ,512), restart);

Button test1(sf::Vector2f(560 ,512), test1Click);

Button test2(sf::Vector2f(624,512), test2Click);

GameState game;

Toolbox::Toolbox() {
    //sets some cool variables B)
    gameState = &game;
    sf::RenderWindow window(sf::VideoMode(800,600), "P4 - Minesweeper, <Brayden Smith>");
    debugMode = false;

    //sets all the buttons to be all set up B)
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
        newGameTexture.loadFromFile("images/face_happy.png");
        sprite.setTexture(newGameTexture);

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

        //intializes the counter sprites
        digits.loadFromFile("images/digits.png");

        counterSign.setPosition(0, 512);
        counterSign.setTexture(digits);
        counterSign.setTextureRect(sf::IntRect (210, 0 , 21, 32));

        digit1.setPosition(21, 512);
        digit1.setTexture(digits);

        digit2.setPosition(42, 512);
        digit2.setTexture(digits);

        digit3.setPosition(63, 512);
        digit3.setTexture(digits);
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
    this->setMineNeighbors();
}

void Toolbox::setMineNeighbors() {

    //sets the neighbor of each tile
    for (int j = 0; j < gameState->getDimensions().x; j++) {
        for(int i = 0; i < gameState->getDimensions().y; i ++) {

            //prefills array with null pointers
            for (int i = 0; i < 8; i++) {
                neighbors[i] = nullptr;
            }

            //checks each corner to see if its valid then sets tiles based on that
            //top left adjacent
            if (j - 1 < 0  || i - 1 < 0) {
                neighbors[0] = nullptr;
            }
            else {
                neighbors[0] = &mines[j - 1][i - 1];
                neighbors[1] = &mines[j][i - 1];
                neighbors[3] = &mines[j - 1][i];
            }
            //top right corner
            if (j + 1 > gameState->getDimensions().x - 1 || i - 1 < 0) {
                neighbors[2] = nullptr;
            }
            else {
                neighbors[1] = &mines[j][i - 1];
                neighbors[2] = &mines[j + 1][i - 1];
                neighbors[4] = &mines[j + 1][i];
            }
            //bottom left corner
            if (j - 1 < 0 || i + 1 > gameState->getDimensions().y - 1 ) {
                neighbors[5] = nullptr;
            }
            else {
                neighbors[3] = &mines[j - 1][i];
                neighbors[5] = &mines[j - 1][i + 1];
                neighbors[6] = &mines[j][i + 1];
            }
            //bottom right corner
            if (j + 1 > gameState->getDimensions().x - 1 || i + 1 > gameState->getDimensions().y - 1) {
                neighbors[7] = nullptr;
            }
            else {
                neighbors[4] = &mines[j + 1][i];
                neighbors[7] = &mines[j + 1][i + 1];
                neighbors[6] = &mines[j][i + 1];
            }

            mines[j][i].setNeighbors(neighbors);
        }
    }
}

//updates the sprites and sends them out to be drawn
std::array<sf::Sprite*, 4> Toolbox::getCounter() {
    int mines = gameState->getMineCount();
    int flags = gameState->getFlagCount();
    int difference = mines - flags;

    std::array<sf::Sprite*, 4> result;

    //if the mine counter is negative it makes the negative sign show up
    if (difference < 0) {
        counterSign.setColor(sf::Color(255,255,255,255));
    }
    else {
        counterSign.setColor(sf::Color(0,0,0,255));
    }

    result[0] = &counterSign;

    difference = abs(difference);
    int numOfDigit;
    //sets the digits to the correct texture block
    numOfDigit = (difference / 100) % 10;
    digit1.setTextureRect(sf::IntRect(numOfDigit * 21,0,21,32));
    result[1] = &digit1;

    numOfDigit = (difference / 10) % 10;
    digit2.setTextureRect(sf::IntRect(numOfDigit * 21,0,21,32));
    result[2] = &digit2;


    numOfDigit = difference % 10;
    digit3.setTextureRect(sf::IntRect(numOfDigit * 21,0,21,32));
    result[3] = &digit3;

    return result;
}