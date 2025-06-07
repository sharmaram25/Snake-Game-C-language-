#pragma once

#include <SDL.h>

class Food {
public:
    Food(int gridWidth, int gridHeight);
    ~Food();

    void reposition(const class Snake& snake);
    void render(SDL_Renderer* renderer, int cellSize);
    void update(float deltaTime);
    
    // Getters
    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x;
    int y;
    int gridWidth;
    int gridHeight;
    float animationTime;
    float pulseFactor;
};
