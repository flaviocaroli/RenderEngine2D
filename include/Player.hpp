#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <string>
#include <vector> 

class Player : public Entity {
private:
    int moveX;
    int moveY;
    int speed;
public:
    Player(const std::string& texture_id, SDL_Renderer* renderer, int x, int y, int w, int h);
    void handleEvent(const SDL_Event& e);
    void update() override; // update based on velocity



};

#endif

