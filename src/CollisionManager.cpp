
#include "Tilemap.hpp"
#include "CollisionManager.hpp"
#include <cstdlib>

bool CollisionManager::mapBoundaryCollision(const SDL_Rect& box, TileMap* tileMap){
    int mapH = tileMap->getCols() * tileMap->getHeight() * 0.55;
    int mapW = tileMap->getRows() * tileMap->getWidth() * 1.75;

    if (box.x < 0) return true;
    if (box.y < 0) return true;
    if (abs(box.x + box.w) > mapW ) return true;
    if (abs(box.y + box.h) > mapH ) return true;

    return false;
}

bool CollisionManager::entityCollision(const SDL_Rect& box, const std::vector<Entity*>& entities, const Entity* ignore){
    for (auto& entity : entities){

        if(entity == ignore){
            continue;
        }
        SDL_Rect other;
        bool isNpc = entity->getW() == 128;
        
        if (isNpc){
        //granular collision with NPCs
            other = {entity->getX() +20, entity->getY() +72 ,
                          entity->getW() -56, entity->getH() -80};
        }
        else{
        //granular collision with trees
            other = {entity->getX() +96, entity->getY() +160 ,
                          entity->getW() - 190, entity->getH() - 165 };
        }
        if (SDL_HasIntersection(&box, &other)){
            return true;
        }
    }
    return false;
}

bool CollisionManager::hasCollision(const SDL_Rect& box, TileMap* tileMap,
                                    const std::vector<Entity*>& entities, const Entity* ignore ){
    if (mapBoundaryCollision(box, tileMap)){
        return true;
    }
    if(entityCollision(box, entities, ignore)){
        return true;
    }

    return false;               
}

Entity* CollisionManager::getCollidingEntity(const SDL_Rect& box, const std::vector<Entity*>& entities, const Entity* ignore) {
    for (auto& entity : entities) {
        if (entity == ignore) {
            continue;
        }
        //same as before, just change the return
        SDL_Rect other;
        bool isNpc = entity->getW() == 128;

        if (isNpc) {
            other = {entity->getX() + 20, entity->getY() + 72,
                     entity->getW() - 56, entity->getH() - 80};
        } else {
            
            other = {entity->getX() + 96, entity->getY() + 160,
                     entity->getW() - 190, entity->getH() - 165};
        }

        if (SDL_HasIntersection(&box, &other)) {
            return entity; 
        }
    }
    return nullptr; 
}