// We want to load textures, fonts, audio, etc., in a safe, C++-friendly manner.
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Player.hpp"
#include "NPC.hpp"

class ResourceManager{
    private:
        static std::unordered_map<std::string, SDL_Texture*> textures;
        static std::vector<Entity*> entities;
    public:
        static SDL_Texture* getTexture(const std::string& file, SDL_Renderer* renderer);
        static void addStaticEntity(const std::string& texturePath, SDL_Renderer* renderer, int x, int y, int w, int h);
        static void addPlayer(Player* player);
        static void addNPC(NPC* npc);
        static const std::vector<Entity*>& getEntities();
        static void clear();

};

#endif