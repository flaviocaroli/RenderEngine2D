// We want to load textures, fonts, audio, etc., in a safe, C++-friendly manner.
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager{
    private:
        static std::unordered_map<std::string, SDL_Texture*> textures;
    public:
        static SDL_Texture* getTexture(const std::string& file, SDL_Renderer* renderer);
        static void clear();
};

#endif