//ResourceManager.cpp

#include "ResourceManager.hpp"
#include <iostream>


std::unordered_map<std::string, SDL_Texture*> ResourceManager::textures;

SDL_Texture* ResourceManager::getTexture(const std::string& file, SDL_Renderer* renderer){

    if(textures.find(file) != textures.end()){ //already loaded
        return textures[file];
    }

    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface){
        std::cerr << "failad to load image" << file << ":" << IMG_GetError() << "\n";
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

void ResourceManager::clear(){
    for (auto& tex : textures) {
        SDL_DestroyTexture(tex.second);
    }
    textures.clear();

}

