//Entity.cpp

#include "Entity.hpp"
#include "ResourceManager.hpp"
#include <SDL2/SDL.h>
#include <iostream>

Entity::Entity(const std::string& texture_id, SDL_Renderer* renderer, int x, int y, int w, int h)
    :renderer(renderer), texture(nullptr), x(x), y(y), w(w), h(h)
{
    texture = ResourceManager::getTexture(texture_id, renderer);
    if(!texture){
        // std::cerr << " error in loading entity" << texture_id << "\n";
 
    }
}

Entity::~Entity(){
    //ResourceManager::getTexture handels that
}

void Entity::update(){
    //nothing by default
}

void Entity::render(int cameraX, int cameraY){

    if (!texture) {
        return;
    }
    SDL_Rect dstRect = {x - cameraX, y -cameraY, w, h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

}