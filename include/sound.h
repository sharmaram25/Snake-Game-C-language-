#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

enum class SoundType {
    EAT,
    GAME_OVER,
    MOVE
};

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool initialize();
    void playSound(SoundType type);
    void clean();

private:
    bool loadSound(SoundType type, const std::string& filePath);
    
    std::unordered_map<SoundType, Mix_Chunk*> sounds;
    bool initialized;
};
