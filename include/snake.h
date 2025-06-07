#pragma once

#include <SDL.h>
#include <vector>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Segment {
    int x;
    int y;
    float visualX;  // For smooth rendering
    float visualY;  // For smooth rendering
};

class Snake {
public:
    Snake(int startX, int startY, int gridWidth, int gridHeight);
    ~Snake();

    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int cellSize);
    void changeDirection(Direction newDirection);
    void grow();
    bool checkCollision();
    bool eatFood(int foodX, int foodY);
    
    // Getters
    int getHeadX() const { return body[0].x; }
    int getHeadY() const { return body[0].y; }
    int getLength() const { return body.size(); }
    const std::vector<Segment>& getBody() const { return body; }

private:
    std::vector<Segment> body;
    Direction direction;
    Direction lastDirection;
    int gridWidth;
    int gridHeight;
    float moveTime;
    float moveDelay;
    bool growing;
};
