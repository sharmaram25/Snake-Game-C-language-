#include "game.h"
#include <iostream>
#include <string>

// Constants
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

Game::Game(const char* title, int width, int height)
    : windowWidth(width), windowHeight(height), isRunning(false),
      gameState(GameState::MENU), score(0), highScore(0), 
      window(nullptr), renderer(nullptr), textRenderer(nullptr), soundManager(nullptr) {
    
    // Calculate grid dimensions based on window size
    cellSize = 20;
    gridWidth = windowWidth / cellSize;
    gridHeight = windowHeight / cellSize;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    // Create window
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    initialize();
    isRunning = true;
}

Game::~Game() {
    clean();
}

void Game::initialize() {
    // Create game objects
    snake = new Snake(gridWidth / 2, gridHeight / 2, gridWidth, gridHeight);
    food = new Food(gridWidth, gridHeight);
    food->reposition(*snake);
    
    // Initialize text renderer
    textRenderer = new Text();
    if (!textRenderer->initialize()) {
        std::cerr << "Failed to initialize text renderer!" << std::endl;
    }
      // Initialize sound manager
    soundManager = new SoundManager();
    if (!soundManager->initialize()) {
        std::cerr << "Failed to initialize sound manager!" << std::endl;
    }
    
    // Initialize grid
    grid = new Grid(gridWidth, gridHeight, cellSize);
    
    // Load high score
    loadHighScore();
    
    // Initialize game state
    gameState = GameState::MENU;
    score = 0;
}

void Game::run() {
    while (isRunning) {
        frameStart = SDL_GetTicks();
        
        handleEvents();
        
        // Update and render based on game state
        switch (gameState) {
            case GameState::PLAYING:
                update();
                render();
                break;
                
            case GameState::MENU:
            case GameState::PAUSED:
            case GameState::GAME_OVER:
                render();
                break;
        }
        
        // Cap the frame rate
        int frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
        
        deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (gameState == GameState::PLAYING) {
                            gameState = GameState::PAUSED;
                        } else if (gameState == GameState::PAUSED) {
                            gameState = GameState::PLAYING;
                        }
                        break;
                        
                    case SDLK_RETURN:
                        if (gameState == GameState::MENU || gameState == GameState::GAME_OVER) {
                            reset();
                            gameState = GameState::PLAYING;
                        }
                        break;
                        
                    case SDLK_p:
                        if (gameState == GameState::PLAYING) {
                            gameState = GameState::PAUSED;
                        } else if (gameState == GameState::PAUSED) {
                            gameState = GameState::PLAYING;
                        }
                        break;
                          case SDLK_UP:
                    case SDLK_w:
                        if (gameState == GameState::PLAYING) {
                            snake->changeDirection(Direction::UP);
                            soundManager->playSound(SoundType::MOVE);
                        }
                        break;
                        
                    case SDLK_DOWN:
                    case SDLK_s:
                        if (gameState == GameState::PLAYING) {
                            snake->changeDirection(Direction::DOWN);
                            soundManager->playSound(SoundType::MOVE);
                        }
                        break;
                          case SDLK_LEFT:
                    case SDLK_a:
                        if (gameState == GameState::PLAYING) {
                            snake->changeDirection(Direction::LEFT);
                            soundManager->playSound(SoundType::MOVE);
                        }
                        break;
                        
                    case SDLK_RIGHT:
                    case SDLK_d:
                        if (gameState == GameState::PLAYING) {
                            snake->changeDirection(Direction::RIGHT);
                            soundManager->playSound(SoundType::MOVE);
                        }
                        break;
                }
                break;
        }
    }
}

void Game::update() {
    snake->update(deltaTime);
    food->update(deltaTime);
      // Check for food consumption
    if (snake->eatFood(food->getX(), food->getY())) {
        score += 10;
        if (score > highScore) {
            highScore = score;
            saveHighScore();
        }
        snake->grow();
        food->reposition(*snake);
        soundManager->playSound(SoundType::EAT);
    }
    
    // Check for collisions
    if (snake->checkCollision()) {
        gameState = GameState::GAME_OVER;
        soundManager->playSound(SoundType::GAME_OVER);
    }
}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Draw game area border
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect border = {0, 0, windowWidth, windowHeight};
    SDL_RenderDrawRect(renderer, &border);
    
    // Render based on game state
    switch (gameState) {
        case GameState::PLAYING:
            renderGameplay();
            break;
            
        case GameState::MENU:
            renderMenu();
            break;
            
        case GameState::PAUSED:
            renderGameplay();
            renderPaused();
            break;
            
        case GameState::GAME_OVER:
            renderGameplay();
            renderGameOver();
            break;
    }
    
    // Update screen
    SDL_RenderPresent(renderer);
}

void Game::renderGameplay() {
    // Render grid background
    grid->render(renderer);
    
    // Render snake and food
    snake->render(renderer, cellSize);
    food->render(renderer, cellSize);
    
    // Display score
    SDL_Color white = {255, 255, 255, 255};
    std::string scoreText = "Score: " + std::to_string(score);
    textRenderer->render(renderer, scoreText, 10, 10, white);
    
    std::string highScoreText = "High Score: " + std::to_string(highScore);
    textRenderer->render(renderer, highScoreText, windowWidth - 180, 10, white);
}

void Game::renderMenu() {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color green = {0, 255, 0, 255};
    
    // Title
    textRenderer->renderCentered(renderer, "CLASSIC SNAKE", windowHeight / 4, green, 48);
    
    // Instructions
    textRenderer->renderCentered(renderer, "Press ENTER to Start", windowHeight / 2, white, 24);
    textRenderer->renderCentered(renderer, "Use Arrow Keys or WASD to control the snake", windowHeight / 2 + 50, white, 24);
    textRenderer->renderCentered(renderer, "P or ESC to Pause", windowHeight / 2 + 100, white, 24);
}

void Game::renderPaused() {
    // Semi-transparent overlay
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &overlay);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // Pause text
    SDL_Color white = {255, 255, 255, 255};
    textRenderer->renderCentered(renderer, "PAUSED", windowHeight / 3, white, 36);
    textRenderer->renderCentered(renderer, "Press P or ESC to Resume", windowHeight / 2, white, 24);
}

void Game::renderGameOver() {
    // Semi-transparent overlay
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &overlay);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    
    // Game over text
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    
    textRenderer->renderCentered(renderer, "GAME OVER", windowHeight / 3, red, 36);
    
    std::string finalScore = "Final Score: " + std::to_string(score);
    textRenderer->renderCentered(renderer, finalScore, windowHeight / 2, white, 24);
    
    textRenderer->renderCentered(renderer, "Press ENTER to Play Again", windowHeight / 2 + 50, white, 24);
}

void Game::clean() {
    // Save high score before quitting
    saveHighScore();
      delete snake;
    delete food;
    
    if (grid) {
        delete grid;
    }
    
    if (textRenderer) {
        textRenderer->clean();
        delete textRenderer;
    }
    
    if (soundManager) {
        soundManager->clean();
        delete soundManager;
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::reset() {
    delete snake;
    delete food;
    
    snake = new Snake(gridWidth / 2, gridHeight / 2, gridWidth, gridHeight);
    food = new Food(gridWidth, gridHeight);
    food->reposition(*snake);
    
    score = 0;
}

void Game::saveHighScore() {
    FILE* file = fopen("highscore.dat", "w");
    if (file) {
        fprintf(file, "%d", highScore);
        fclose(file);
    }
}

void Game::loadHighScore() {
    FILE* file = fopen("highscore.dat", "r");
    if (file) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    } else {
        highScore = 0;
    }
}
