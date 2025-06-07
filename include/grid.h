#pragma once

#include <SDL.h>

class Grid {
public:
    Grid(int gridWidth, int gridHeight, int cellSize);
    ~Grid();

    void render(SDL_Renderer* renderer);

private:
    int gridWidth;
    int gridHeight;
    int cellSize;
};
