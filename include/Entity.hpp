#ifndef ENTITY_hpp
#define ENTITY_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Entity{
protected: //because its a base class
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int x, y;
    int w, h;

public:
    Entity(const std::string& texture_id, SDL_Renderer* renderer, int x, int y, int w, int h);

    virtual ~Entity();
    virtual void render(int cameraX, int cameraY);
    virtual void update();

    int getX() {return x;}
    int getY() {return y;}
    void setX(int newX) {x = newX;}
    void setY(int newY) {y = newY;}

};

#endif