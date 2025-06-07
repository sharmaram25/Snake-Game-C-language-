#include "text.h"
#include <iostream>

Text::Text()
    : font24(nullptr), font36(nullptr), font48(nullptr) {
    fontPath = "assets/fonts/ARCADE_I.TTF";
}

Text::~Text() {
    clean();
}

bool Text::initialize() {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    // Load fonts
    font24 = loadFont(24);
    font36 = loadFont(36);
    font48 = loadFont(48);
    
    return (font24 != nullptr);
}

TTF_Font* Text::loadFont(int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        std::cerr << "Attempting to use default font..." << std::endl;
        
        // Try to load a default system font on Windows
        font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", fontSize);
        if (!font) {
            std::cerr << "Failed to load default font! TTF_Error: " << TTF_GetError() << std::endl;
        } else {
            fontPath = "C:\\Windows\\Fonts\\arial.ttf";
        }
    }
    return font;
}

void Text::render(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize) {
    if (text.empty()) {
        return;
    }
    
    // Select the appropriate font based on size
    TTF_Font* selectedFont = nullptr;
    if (fontSize <= 24) {
        selectedFont = font24;
    } else if (fontSize <= 36) {
        selectedFont = font36;
    } else {
        selectedFont = font48;
    }
    
    if (!selectedFont) {
        selectedFont = loadFont(fontSize);
        if (!selectedFont) {
            return;
        }
    }
    
    // Render text to surface
    SDL_Surface* textSurface = TTF_RenderText_Blended(selectedFont, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    
    // Create texture from surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    
    // Set render destination
    SDL_Rect renderRect = {x, y, textSurface->w, textSurface->h};
    
    // Render texture to screen
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderRect);
    
    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Text::renderCentered(SDL_Renderer* renderer, const std::string& text, int y, SDL_Color color, int fontSize) {
    if (text.empty()) {
        return;
    }
    
    // Select the appropriate font based on size
    TTF_Font* selectedFont = nullptr;
    if (fontSize <= 24) {
        selectedFont = font24;
    } else if (fontSize <= 36) {
        selectedFont = font36;
    } else {
        selectedFont = font48;
    }
    
    if (!selectedFont) {
        selectedFont = loadFont(fontSize);
        if (!selectedFont) {
            return;
        }
    }
    
    // Get text dimensions
    int textWidth, textHeight;
    if (TTF_SizeText(selectedFont, text.c_str(), &textWidth, &textHeight) != 0) {
        std::cerr << "Unable to calculate text size! TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }
    
    // Get renderer dimensions
    int rendererWidth, rendererHeight;
    SDL_GetRendererOutputSize(renderer, &rendererWidth, &rendererHeight);
    
    // Calculate centered x position
    int x = (rendererWidth - textWidth) / 2;
    
    // Render the text
    render(renderer, text, x, y, color, fontSize);
}

void Text::clean() {
    if (font24) {
        TTF_CloseFont(font24);
        font24 = nullptr;
    }
    
    if (font36) {
        TTF_CloseFont(font36);
        font36 = nullptr;
    }
    
    if (font48) {
        TTF_CloseFont(font48);
        font48 = nullptr;
    }
    
    TTF_Quit();
}
