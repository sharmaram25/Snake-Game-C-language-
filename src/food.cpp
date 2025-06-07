#include "food.h"
#include "snake.h"
#include <cstdlib>
#include <ctime>
#include <cmath>  // For sin function

Food::Food(int gridWidth, int gridHeight)
    : x(0), y(0), gridWidth(gridWidth), gridHeight(gridHeight), 
      animationTime(0.0f), pulseFactor(1.0f) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Food::~Food() {
    // Nothing to clean up
}

void Food::reposition(const Snake& snake) {
    // Find a random position that is not occupied by the snake
    bool validPosition = false;
    
    while (!validPosition) {
        x = std::rand() % gridWidth;
        y = std::rand() % gridHeight;
        
        validPosition = true;
        
        // Check if the position is occupied by any part of the snake
        const std::vector<Segment>& snakeBody = snake.getBody();
        for (const auto& segment : snakeBody) {
            if (segment.x == x && segment.y == y) {
                validPosition = false;
                break;
            }
        }
    }
}

void Food::update(float deltaTime) {
    // Update the animation time
    animationTime += deltaTime * 4.0f;
    
    // Calculate pulse factor using sine wave (0.8 to 1.2)
    pulseFactor = 1.0f + 0.2f * sin(animationTime);
}

void Food::render(SDL_Renderer* renderer, int cellSize) {
    // Draw food as a red circle (approximated with a filled rectangle)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    
    // Apply pulsating effect
    int pulseSize = static_cast<int>(cellSize * pulseFactor);
    int offset = (cellSize - pulseSize) / 2;
    
    SDL_Rect foodRect = {
        x * cellSize + offset,
        y * cellSize + offset,
        pulseSize,
        pulseSize
    };
    
    SDL_RenderFillRect(renderer, &foodRect);
}
