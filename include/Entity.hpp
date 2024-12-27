#ifndef ENTITY.hpp
#define ENTITY.hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Entity{
protected: //because its a base class
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int x, y;

public:
    Entity(const std::str& texture_id, SDL_Renderer* renderer, int x, int y);

    ~Entity();
    virtual void render();
    virtual void update();

    int getX() {return x;}
    int getY() {return y;}

};

#endif