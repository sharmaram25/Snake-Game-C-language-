#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text {
public:
    Text();
    ~Text();

    bool initialize();
    void render(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize = 24);
    void renderCentered(SDL_Renderer* renderer, const std::string& text, int y, SDL_Color color, int fontSize = 24);
    void clean();

private:
    TTF_Font* loadFont(int fontSize);
    
    std::string fontPath;
    TTF_Font* font24;
    TTF_Font* font36;
    TTF_Font* font48;
};
