/*
 * Classic Snake Game
 * Author: Ram Sharma
 * Copyright (c) 2025 Ram Sharma
 * 
 * A modern C++ implementation of the classic Snake game using SDL2
 */

#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    
    // Create and run the game
    Game game("Classic Snake", WINDOW_WIDTH, WINDOW_HEIGHT);
    game.run();
    
    return 0;
}
