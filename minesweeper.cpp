#include "minesweeper.h"

int launch() {

    //recreates the window
    Toolbox& Toolbox = Toolbox::getInstance();
    Toolbox.window.create(sf::VideoMode(800,600), "P4 - Minesweeper, <Brayden Smith>");

    //runs the window rendering loop
    while (Toolbox.window.isOpen()) {

        //looks for events on each frame from player
        sf::Event event;
        while (Toolbox.window.pollEvent(event)) {

            //closes the window if clicked
            if (event.type == sf::Event::Closed)
                Toolbox.window.close();

            //runs logic if left mouse click happens
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                //gets the mouse position on click then compares it to the area of each of the buttons
                sf::Vector2i mousePosition = sf::Mouse::getPosition(Toolbox.window);
                for (int i = 0; i < 4; i++)
                {
                    //if the click is in the rectangle of the button it does its on click function
                    sf::FloatRect range = Toolbox.buttons[i]->getSprite()->getGlobalBounds();
                    if (range.contains(mousePosition.x, mousePosition.y))
                    {
                        Toolbox.buttons[i]->onClick();
                    }

                    //if the left click is on a tile it calls that tiles left click function
                    Tile* tilePntr = Toolbox.gameState->getTile(mousePosition.x, mousePosition.y);

                    if (!(tilePntr == nullptr)) {
                        tilePntr->onClickLeft();
                    }
                }
            }
            //runs the logic if there is a right button clicked
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                //gets mouse position then checks to see if there is a tile there
                sf::Vector2i mousePosition = sf::Mouse::getPosition(Toolbox.window);
                Tile* tilePntr = Toolbox.gameState->getTile(mousePosition.x, mousePosition.y);

                if (!(tilePntr == nullptr)) {
                    tilePntr->onClickRight();
                }
            }
        }

        //clear the window to render new frame
        Toolbox.window.clear(sf::Color(255,255,255,255));

        //draw the data
        render();

        //display the current frame on screen
        Toolbox.window.display();
    }

    return 0;
}

sf::Texture texture;

//resets all objects, generates a default game state and turns off debug mode
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (getDebugMode()) {
        toggleDebugMode();
    }

    //resets the reset buttons smile :)
    texture.loadFromFile("images/face_happy.png");
    toolbox.buttons[1]->getSprite()->setTexture(texture);

    //resets gamestate
    //toolbox.gameState = &newGameState;
}

//renders the current game state
void render() {
    Toolbox& Toolbox = Toolbox::getInstance();
    for (int i = 0; i < 4; i++)
    {
        Toolbox.window.draw(*Toolbox.buttons[i]->getSprite());
    }

    for (int i = 0; i < 25; i ++) {
        for (int j = 0; j < 16; j ++) {
            Toolbox.gameState->getTile(i*32,j*32)->draw();
        }
    }

    for (int j = 0; j < 25; j++) {
        for(int i = 0; i < 16; i ++) {
            Toolbox.window.draw(*Toolbox.mines[j][i].getSprite());
        }
    }
}

//looks at if debug mode and swaps its value
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    bool debug = toolbox.debugMode;

    if (!debug) {
        Toolbox::getInstance().debugMode = true;
        for (int i = 0; i < toolbox.gameState->getDimensions().x; i++) {
            for (int j = 0; j < toolbox.gameState->getDimensions().y; j++) {
                toolbox.mines[i][j].setColor(sf::Color(255,255,255, 255));
            }
        }
    }
    else {
        Toolbox::getInstance().debugMode = false;
        for (int i = 0; i < toolbox.gameState->getDimensions().x; i++) {
            for (int j = 0; j < toolbox.gameState->getDimensions().y; j++) {
                toolbox.mines[i][j].setColor(sf::Color(0,0,0, 0));
            }
        }
    }

}

//returns which state debug mode is in
bool getDebugMode() {
    return Toolbox::getInstance().debugMode;
}

void lost() {
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Texture texture;
    texture.loadFromFile("images/face_lose.png");
    toolbox.buttons[1]->getSprite()->setTexture(texture);

    //draws finale frame then waits a bit before restarting
    toolbox.window.clear(sf::Color(255,255,255,255));
    render();
    toolbox.window.display();
    Sleep(500);

    restart();
}