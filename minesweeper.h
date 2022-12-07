#pragma once
#include "Toolbox.h"
#include "Tile.h"
#include <vector>
#include <windows.h>

//prototypes the global functions
int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();
void lost();
bool winCheck();
void won();