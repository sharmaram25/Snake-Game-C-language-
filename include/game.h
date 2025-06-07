#pragma once

#include <SDL.h>
#include <vector>
#include <string>
#include "snake.h"
#include "food.h"
#include "text.h"
#include "sound.h"
#include "grid.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
public:
    Game(const char* title, int width, int height);
    ~Game();

    void run();

private:
    void initialize();
    void handleEvents();
    void update();
    void render();
    void renderText();
    void renderGameplay();
    void renderMenu();
    void renderPaused();
    void renderGameOver();
    void clean();
    void reset();
    void generateFood();
    void saveHighScore();
    void loadHighScore();

    // Window dimensions
    int windowWidth;
    int windowHeight;

    // Grid dimensions
    int gridWidth;
    int gridHeight;
    int cellSize;    // Game objects
    Snake* snake;
    Food* food;
    Text* textRenderer;
    SoundManager* soundManager;
    Grid* grid;

    // Game properties
    bool isRunning;
    GameState gameState;
    int score;
    int highScore;
    unsigned int frameStart;
    float deltaTime;
    
    // SDL components
    SDL_Window* window;
    SDL_Renderer* renderer;
};
