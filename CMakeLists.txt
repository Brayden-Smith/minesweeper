cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper main.cpp minesweeper.cpp minesweeper.h Toolbox.cpp Toolbox.h Tile.cpp Tile.h Button.cpp Button.h GameState.cpp GameState.h mine.cpp mine.h mine.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Libraries/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics audio REQUIRED)

include_directories(c:/Libraries/SFML/include)
target_link_libraries(minesweeper sfml-graphics sfml-audio)