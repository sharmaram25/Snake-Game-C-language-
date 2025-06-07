#include "snake.h"

Snake::Snake(int startX, int startY, int gridWidth, int gridHeight)
    : direction(Direction::RIGHT), lastDirection(Direction::RIGHT),
      gridWidth(gridWidth), gridHeight(gridHeight), moveTime(0.0f),
      moveDelay(0.1f), growing(false) {
    
    // Initialize the snake with a head segment
    body.push_back({startX, startY, (float)startX, (float)startY});
    
    // Add a few initial segments to make the snake visible
    body.push_back({startX - 1, startY, (float)(startX - 1), (float)startY});
    body.push_back({startX - 2, startY, (float)(startX - 2), (float)startY});
}

Snake::~Snake() {
    // Nothing to clean up
}

void Snake::update(float deltaTime) {
    // Update movement timer
    moveTime += deltaTime;
    
    // Update visual positions (for smooth animation)
    const float animationSpeed = 10.0f;
    for (auto& segment : body) {
        segment.visualX = segment.visualX + (segment.x - segment.visualX) * deltaTime * animationSpeed;
        segment.visualY = segment.visualY + (segment.y - segment.visualY) * deltaTime * animationSpeed;
    }
    
    // Move the snake when the delay time has passed
    if (moveTime >= moveDelay) {
        moveTime = 0;
        lastDirection = direction;
        
        // If the snake is growing, don't remove the tail
        if (!growing) {
            // Move all segments except the head
            for (size_t i = body.size() - 1; i > 0; --i) {
                body[i].x = body[i - 1].x;
                body[i].y = body[i - 1].y;
            }
        } else {
            // The snake is growing, so add a new segment at the head position
            Segment newSegment = body[0];
            body.insert(body.begin() + 1, newSegment);
            growing = false;
        }
          // Move the head in the current direction
        switch (direction) {
            case Direction::UP:
                body[0].y--;
                break;
            case Direction::DOWN:
                body[0].y++;
                break;
            case Direction::LEFT:
                body[0].x--;
                break;
            case Direction::RIGHT:
                body[0].x++;
                break;
        }
        
        // Gradually decrease move delay as snake grows (increase speed)
        if (body.size() > 5 && moveDelay > 0.05f) {
            moveDelay = 0.1f - (body.size() - 5) * 0.002f;
            if (moveDelay < 0.05f) moveDelay = 0.05f; // Cap at a minimum delay
        }
    }
}

void Snake::render(SDL_Renderer* renderer, int cellSize) {
    // Draw snake body segments (from tail to head)
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); // Slightly darker green
    for (size_t i = body.size() - 1; i > 0; --i) {
        SDL_Rect segmentRect = {
            static_cast<int>(body[i].visualX * cellSize),
            static_cast<int>(body[i].visualY * cellSize),
            cellSize,
            cellSize
        };
        SDL_RenderFillRect(renderer, &segmentRect);
    }
    
    // Draw snake head
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    SDL_Rect headRect = {
        static_cast<int>(body[0].visualX * cellSize),
        static_cast<int>(body[0].visualY * cellSize),
        cellSize,
        cellSize
    };
    SDL_RenderFillRect(renderer, &headRect);
    
        // Draw snake eyes (simple detail)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    int eyeSize = cellSize / 4;
    int eyeOffset = cellSize / 4;
    
    // Position eyes based on direction
    SDL_Rect leftEye, rightEye;
    switch (direction) {
        case Direction::UP:
            leftEye = {headRect.x + eyeOffset, headRect.y + eyeOffset, eyeSize, eyeSize};
            rightEye = {headRect.x + cellSize - eyeOffset - eyeSize, headRect.y + eyeOffset, eyeSize, eyeSize};
            break;
        case Direction::DOWN:
            leftEye = {headRect.x + eyeOffset, headRect.y + cellSize - eyeOffset - eyeSize, eyeSize, eyeSize};
            rightEye = {headRect.x + cellSize - eyeOffset - eyeSize, headRect.y + cellSize - eyeOffset - eyeSize, eyeSize, eyeSize};
            break;
        case Direction::LEFT:
            leftEye = {headRect.x + eyeOffset, headRect.y + eyeOffset, eyeSize, eyeSize};
            rightEye = {headRect.x + eyeOffset, headRect.y + cellSize - eyeOffset - eyeSize, eyeSize, eyeSize};
            break;
        case Direction::RIGHT:
            leftEye = {headRect.x + cellSize - eyeOffset - eyeSize, headRect.y + eyeOffset, eyeSize, eyeSize};
            rightEye = {headRect.x + cellSize - eyeOffset - eyeSize, headRect.y + cellSize - eyeOffset - eyeSize, eyeSize, eyeSize};
            break;
    }
    
    SDL_RenderFillRect(renderer, &leftEye);
    SDL_RenderFillRect(renderer, &rightEye);

    // Draw body segments
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255); // Green body
    for (size_t i = 1; i < body.size(); ++i) {
        SDL_Rect segmentRect = {
            body[i].x * cellSize + 1,
            body[i].y * cellSize + 1,
            cellSize - 2,
            cellSize - 2
        };        SDL_RenderFillRect(renderer, &segmentRect);
    }
}

void Snake::changeDirection(Direction newDirection) {
    // Prevent 180-degree turns
    if ((newDirection == Direction::UP && lastDirection != Direction::DOWN) ||
        (newDirection == Direction::DOWN && lastDirection != Direction::UP) ||
        (newDirection == Direction::LEFT && lastDirection != Direction::RIGHT) ||
        (newDirection == Direction::RIGHT && lastDirection != Direction::LEFT)) {
        direction = newDirection;
    }
}

void Snake::grow() {
    growing = true;
}

bool Snake::checkCollision() {
    int headX = body[0].x;
    int headY = body[0].y;
    
    // Check for collision with walls
    if (headX < 0 || headX >= gridWidth || headY < 0 || headY >= gridHeight) {
        return true;
    }
    
    // Check for collision with snake's own body (skip the head)
    for (size_t i = 1; i < body.size(); ++i) {
        if (headX == body[i].x && headY == body[i].y) {
            return true;
        }
    }
    
    return false;
}

bool Snake::eatFood(int foodX, int foodY) {
    // Check if the snake's head is at the food position
    return (body[0].x == foodX && body[0].y == foodY);
}
