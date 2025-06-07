#include "sound.h"
#include <iostream>

SoundManager::SoundManager() : initialized(false) {
    // Initialize sounds map with nullptr
    sounds[SoundType::EAT] = nullptr;
    sounds[SoundType::GAME_OVER] = nullptr;
    sounds[SoundType::MOVE] = nullptr;
}

SoundManager::~SoundManager() {
    clean();
}

bool SoundManager::initialize() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    // Create sounds directory if it doesn't exist
    // Load sound files
    bool loadSuccess = true;
    loadSuccess &= loadSound(SoundType::EAT, "assets/sounds/eat.wav");
    loadSuccess &= loadSound(SoundType::GAME_OVER, "assets/sounds/game_over.wav");
    loadSuccess &= loadSound(SoundType::MOVE, "assets/sounds/move.wav");
    
    // Fall back to system sounds if not available
    if (!loadSuccess) {
        std::cerr << "Could not load all sound files. Game will continue without sound." << std::endl;
    }
    
    initialized = true;
    return true;
}

bool SoundManager::loadSound(SoundType type, const std::string& filePath) {
    // Check if sound is already loaded
    if (sounds[type] != nullptr) {
        Mix_FreeChunk(sounds[type]);
        sounds[type] = nullptr;
    }
    
    // Load sound file
    sounds[type] = Mix_LoadWAV(filePath.c_str());
    if (!sounds[type]) {
        std::cerr << "Failed to load sound effect: " << filePath << " Mix_Error: " << Mix_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void SoundManager::playSound(SoundType type) {
    if (!initialized) return;
    
    if (sounds[type]) {
        Mix_PlayChannel(-1, sounds[type], 0);
    }
}

void SoundManager::clean() {
    // Free all loaded sounds
    for (auto& pair : sounds) {
        if (pair.second) {
            Mix_FreeChunk(pair.second);
            pair.second = nullptr;
        }
    }
    
    // Close SDL_mixer
    Mix_CloseAudio();
    initialized = false;
}
