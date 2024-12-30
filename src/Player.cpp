//Player.cpp


#include "Player.hpp"
#include <iostream>
#include <string>


Player::Player(const std::string& texture_id, SDL_Renderer* renderer, int x, int y, int w, int h)
    : Entity(texture_id, renderer, x, y, w, h),
      moveX(0),
      moveY(0),
      speed(1)
{}

void Player::handleEvent(const SDL_Event& e) {
    // Key down (press)
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: moveY = -speed; break; // up
            case SDLK_a: moveX = -speed; break; // left
            case SDLK_s: moveY =  speed; break; // down
            case SDLK_d: moveX =  speed; break; // right
            default: break;
        }
    }
    // Key up (release)
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w:
                if ( moveY < 0) {
                     moveY = 0;
                }
                break;
            case SDLK_a:
                if (moveX < 0) {
                    moveX = 0;
                }
                break;
            case SDLK_s:
                if ( moveY > 0) {
                     moveY = 0;
                }
                break;
            case SDLK_d:
                if (moveX > 0) {
                    moveX = 0;
                }
                break;
            default: break;
        }
    }
}


void Player::update() {
    // Move according to velocity
    x += moveX;
    y += moveY;
}

