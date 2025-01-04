//ResourceManager.cpp

#include "ResourceManager.hpp"
#include <iostream>


std::unordered_map<std::string, SDL_Texture*> ResourceManager::textures;
std::vector<Entity*> ResourceManager::entities;

SDL_Texture* ResourceManager::getTexture(const std::string& file, SDL_Renderer* renderer){

    if(textures.find(file) != textures.end()){ //already loaded
        return textures[file];
    }

    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface){
        std::cerr << "failed to load image" << file << ":" << IMG_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!new_texture){
        std::cerr << "failad to create texture" << file << ":" << SDL_GetError() << "\n";
        return nullptr;
    }
    textures[file] = new_texture;
    return new_texture;

}

const std::vector<Entity*>& ResourceManager::getEntities() {
    return entities;
}

void ResourceManager::addPlayer(Player* player) {
    if (player) {
        entities.push_back(player);
    } else {
        std::cerr << "Failed to add player: nullptr provided" << std::endl;
    }
}

void ResourceManager::addStaticEntity(const std::string& texturePath, SDL_Renderer* renderer, int x, int y, int w, int h){
    SDL_Texture* texture = getTexture(texturePath, renderer);
    if (texture){
        Entity* entity = new Entity(texturePath, renderer, x, y, w, h);
        entities.push_back(entity);
    }
    else {
        std::cerr << "Failed to create entity with texture: " << texturePath << std::endl;

    }
}


void ResourceManager::clear(){
    for (auto& tex : textures) {
        SDL_DestroyTexture(tex.second);
    }
    textures.clear();

    for (auto& entity: entities){
        delete entity;
    }
    entities.clear();

}

