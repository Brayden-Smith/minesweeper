#include "GameState.h"

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    dimensions = _dimensions;
    numberofmines = _numberOfMines;
    status = GameState::PLAYING;

    //sets the size of the 2d vector
    tiles = std::vector<std::vector<Tile>>(dimensions.x);
    for (int i = 0; i < dimensions.x; i++) {
        tiles[i] = std::vector<Tile>(dimensions.y);
    }


    //sets all the tiles in the vector
    for (int j = 0; j < dimensions.x; j++) {
        for(int i = 0; i < dimensions.y; i ++) {
            Tile tile(sf::Vector2f(32 * j, 32 * i));
            tiles[j][i] = tile;
        }
    }

    //creates and sets the size of the mine vector
    std::vector<std::vector<int>> mineBoard;
    mineBoard = std::vector<std::vector<int>>(dimensions.x);
    for (int i = 0; i < dimensions.x; i++) {
        mineBoard[i] = std::vector<int>(dimensions.y);
    }

    //seeds the randomness based on time
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < numberofmines; i++) {
        bool placed = false;
        while (!placed) {
            int randomX = rand() % (dimensions.x);
            int randomY = rand() % (dimensions.y);
            if (mineBoard[randomX][randomY] == 0) {
                placed = true;
                mineBoard[randomX][randomY] = 1;
            }
        }
    }

    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.createBoard(mineBoard);
}

GameState::GameState(const char *filepath) {

    //creates a File stream and opens the file
    std::fstream boardFile;
    boardFile.open(filepath, std::ios::in);
    if(!boardFile.is_open()) {
        throw std::invalid_argument("File does not exist");
    }

    //reads in the data to a string then closes the file
    std::string line;
    std::vector<std::string> totalBoard;
    int rows;

    while (!boardFile.eof())
    {
        std::getline(boardFile, line);
        totalBoard.push_back(line);
        rows++;
    }
    boardFile.close();

    int columns = line.length();
    dimensions = sf::Vector2i(columns,rows);

    //counts the number of mines on the board
    numberofmines = 0;
    for (int j = 0; j < totalBoard.size(); j ++)
    {
        for (int i = 0; i < totalBoard[j].size(); i++)
        {
            if (totalBoard[j].at(i) == *"1")
            {
                numberofmines++;
            }
        }
    }


    //pass the read in board to toolbox
    Toolbox& toolbox = Toolbox::getInstance();
    //toolbox.createBoard(realBoard);

    //creates the 2d Vector of tiles
    for (int j = 0; j < dimensions.x; j++) {
        for(int i = 0; i < dimensions.y; i ++) {
            Tile tile(sf::Vector2f(32 * j, 32 * i));
            tiles[j][i] = tile;
        }
    }
}

GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}

void GameState::setPlayStatus(PlayStatus _status) {
    status = _status;
}

int GameState::getMineCount() {
    return numberofmines;
}

//returns number of flags on the board
int GameState::getFlagCount() {
    //look through each tile to see if flagged then return num
    int flags;
    for (int j = 0; j < dimensions.x; j++) {
        for(int i = 0; i < dimensions.y; i ++) {
            if (tiles[j][i].getState() == Tile::FLAGGED) {
                flags++;
            }
        }
    }
    return flags;
}

//retursn the dimensions of the gamestate
sf::Vector2i GameState::getDimensions() {
    return dimensions;
}

Tile* GameState::getTile(int x, int y) {

    //turns x and y into nearest multiple of 32 so that it fits a possible tile
    if (y % 32 > 0) {
        y -= (y % 32);
    }

    if (x % 32 > 0) {
        x -= (x % 32);
    }


    //see if it's in range of the tiles
    if (y > 480 || y < 0) {
        return nullptr;
    }
    if (x > 800 || x < 0) {
        return nullptr;
    }

    //finds the tile in the 2d array
    return &tiles[x / 32][y / 32];
}