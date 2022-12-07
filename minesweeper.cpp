#include "minesweeper.h"

//checks every tile to see if none mine spots have revealed tiles
bool winCheck() {
    Toolbox& toolbox = Toolbox::getInstance();
    for (int j = 0; j < toolbox.gameState->getDimensions().x; j++) {
        for(int i = 0; i < toolbox.gameState->getDimensions().y; i ++) {
            if(!toolbox.mines[j][i].doesExist() && toolbox.gameState->getTile(j,i)->getState() != Tile::REVEALED) {
                return false;
            }
        }
    }
    return true;
}

//changes the face to win face then resets after some time
void won() {
    Toolbox& toolbox = Toolbox::getInstance();

    toolbox.newGameTexture.loadFromFile("images/face_win.png");
    toolbox.buttons[1]->getSprite()->setTexture(toolbox.newGameTexture);

    //draws finale frame then waits a bit before restarting
    toolbox.window.clear(sf::Color(255,255,255,255));
    render();
    toolbox.window.display();
}

int launch() {

    //recreates the window and creates the gameState
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

                    if (tilePntr != nullptr) {
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


//resets all objects, generates a default game state and turns off debug mode
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();

    //debug mode back to false
    if (getDebugMode()) {
        toggleDebugMode();
    }

    //resets the reset buttons smile :)
    toolbox.newGameTexture.loadFromFile("images/face_happy.png");
    toolbox.buttons[1]->getSprite()->setTexture(toolbox.newGameTexture);

    //resets gamestate
    toolbox.gameState->setPlayStatus(GameState::WIN);
}

//renders the current game state
void render() {
    Toolbox& Toolbox = Toolbox::getInstance();
    for (int i = 0; i < 4; i++)
    {
        Toolbox.window.draw(*Toolbox.buttons[i]->getSprite());
    }

    sf::Vector2i dimensions = Toolbox.gameState->getDimensions();
    for (int i = 0; i < dimensions.x; i ++) {
        for (int j = 0; j < dimensions.y; j ++) {
            Toolbox.gameState->getTile(i*32,j*32)->draw();
        }
    }

    for (int j = 0; j < dimensions.x; j++) {
        for(int i = 0; i < dimensions.y; i ++) {
            if (Toolbox.mines[j][i].isDrawn) {
                Toolbox.window.draw(*Toolbox.mines[j][i].getSprite());
            }
        }
    }
}

//looks at if debug mode and swaps its value
void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    bool debug = toolbox.debugMode;

    //sets the transparency of the mines depending on if debug mode is now on or not
    if (!debug) {
        Toolbox::getInstance().debugMode = true;
        for (int i = 0; i < toolbox.gameState->getDimensions().x; i++) {
            for (int j = 0; j < toolbox.gameState->getDimensions().y; j++) {
                if(toolbox.mines[i][j].doesExist())
                {
                    toolbox.mines[i][j].setColor(sf::Color(255, 255, 255, 255));
                }
            }
        }
    }
    else {
        Toolbox::getInstance().debugMode = false;
        for (int i = 0; i < toolbox.gameState->getDimensions().x; i++) {
            for (int j = 0; j < toolbox.gameState->getDimensions().y; j++) {
                if(toolbox.mines[i][j].doesExist())
                {
                    toolbox.mines[i][j].setColor(sf::Color(255, 255, 255, 0));
                }
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

    toolbox.newGameTexture.loadFromFile("images/face_lose.png");
    toolbox.buttons[1]->getSprite()->setTexture(toolbox.newGameTexture);

    //draws finale frame then waits a bit before restarting
    toolbox.window.clear(sf::Color(255,255,255,255));
    render();
    toolbox.window.display();

}