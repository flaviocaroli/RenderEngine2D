
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

bool CollisionManager::entityCollision(const SDL_Rect& box, std::vector<Entity*>& entities, const Entity* ignore){
    for (auto& entity : entities){

        if(entity == ignore){
            continue;
        }
        SDL_Rect other;
        //more granular collision with trees
        other = {entity->getX() +96, entity->getY() +160 ,
                          entity->getW() - 190, entity->getH() - 165 };
        if (SDL_HasIntersection(&box, &other)){
            return true;
        }
    }
    return false;
}

bool CollisionManager::hasCollision(const SDL_Rect& box, TileMap* tileMap,
                                    std::vector<Entity*>& entities, const Entity* ignore ){
    if (mapBoundaryCollision(box, tileMap)){
        return true;
    }
    if(entityCollision(box, entities, ignore)){
        return true;
    }

    return false;               
}