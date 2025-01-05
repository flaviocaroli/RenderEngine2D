#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <SDL2/SDL.h>
#include <vector>
#include "Entity.hpp"
#include "TileMap.hpp"

class CollisionManager{
public:
    bool mapBoundaryCollision(const SDL_Rect& box, TileMap* tileMap);
    bool entityCollision(const SDL_Rect& box, const std::vector<Entity*>& entities, const Entity* ignore);

    //helper
    bool hasCollision(const SDL_Rect& box, TileMap* tileMap,
                      const std::vector<Entity*>& entities, const Entity* ignore );
    Entity* getCollidingEntity(const SDL_Rect& box, const std::vector<Entity*>& entities, const Entity* ignore);

};

#endif