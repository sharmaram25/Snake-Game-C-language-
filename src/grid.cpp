#include "grid.h"

Grid::Grid(int gridWidth, int gridHeight, int cellSize)
    : gridWidth(gridWidth), gridHeight(gridHeight), cellSize(cellSize) {
}

Grid::~Grid() {
    // Nothing to clean up
}

void Grid::render(SDL_Renderer* renderer) {
    // Set grid line color (dark gray)
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    
    // Draw vertical grid lines
    for (int x = 0; x <= gridWidth; ++x) {
        SDL_RenderDrawLine(
            renderer,
            x * cellSize, 0,
            x * cellSize, gridHeight * cellSize
        );
    }
    
    // Draw horizontal grid lines
    for (int y = 0; y <= gridHeight; ++y) {
        SDL_RenderDrawLine(
            renderer,
            0, y * cellSize,
            gridWidth * cellSize, y * cellSize
        );
    }
}
