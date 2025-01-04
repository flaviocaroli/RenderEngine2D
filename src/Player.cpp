//Player.cpp


#include "Player.hpp"
#include <iostream>
#include <string>
#include "ResourceManager.hpp"


Player::Player(const std::string& idle_path,
               const std::string& walk_path, 
               SDL_Renderer* renderer, int x, int y, int w, int h)
    : Entity("", renderer, x, y, w, h),
      moveX(0),
      moveY(0),
      speed(1),
      currentDir(Direction::DOWN),
      currentAnim(AnimationState::IDLE),
      isMoving(false),
      currentFrame(0),
      idleTexture(nullptr),
      walkTexture(nullptr),
      frameWidth(64),
      frameHeight(64),
      frameTime(100),     // 120 ms per frame, for instance
      lastFrameTick(0)

{   
    frameCount[0] = 2;
    frameCount[1] = 6;
    idleTexture = ResourceManager::getTexture(idle_path, renderer);
    walkTexture = ResourceManager::getTexture(walk_path, renderer);

    if(!walkTexture){
        std::cerr << "Failed to load sprite" << walk_path << "\n";
    }
    if(!idleTexture){
        std::cerr << "Failed to load sprite" << idle_path << "\n";
    }
    
}

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


void Player::update() { //calculates the frame to use in the render function
    // Move according to velocity
    x += moveX;
    y += moveY;

    //Movement animation logic
    isMoving = (moveX != 0 || moveY != 0);

    updateDir();
    updateAnim();

    //Animation
    if (isMoving){
        Uint32 now = SDL_GetTicks(); // time in ms since SDL init
        //now - lastFrameTick is the amount of time that has passed since we last updated the animation frame
        if (now - lastFrameTick >= frameTime) {
            //advance to next frame
            lastFrameTick = now;

            int total;
            if (currentAnim == AnimationState::IDLE){
                total = frameCount[0];
            }
            else if (currentAnim == AnimationState::WALK){
                total = frameCount[1];
            }

            currentFrame = (currentFrame + 1) % total; 
            // cycles 0->1->2->...->7->0->...
        }
    }
    else{
        currentFrame = 0;
    }   
}

void Player::render(int cameraX, int cameraY){
    
    SDL_Texture* currentTex = nullptr;

    if (currentAnim == AnimationState::IDLE){
            currentTex = idleTexture;
        }
    else if (currentAnim == AnimationState::WALK){
            currentTex = walkTexture;
        }

    if (!currentTex) return;


    // Convert currentDirection to row index
    // We'll assume row order: 0=DOWN, 1=LEFT, 2=RIGHT, 3=UP
    int rowIndex = static_cast<int>(currentDir);
    int colIndex = currentFrame;

    SDL_Rect srcRect;
    srcRect.x = colIndex * frameWidth; //from the texture image gets the sprite to display
    srcRect.y = rowIndex * frameHeight;
    srcRect.w = frameWidth;
    srcRect.h = frameHeight;


    
    SDL_Rect dstRect;
    dstRect.x = x - cameraX;
    dstRect.y = y - cameraY;
    dstRect.w = w; 
    dstRect.h = h;  

    SDL_RenderCopy(renderer, currentTex, &srcRect, &dstRect);
}

void Player::updateDir()
{
    if (!isMoving) {
        return;
    }

    // If moving vertically but not horizontally, pick up/down
    if (moveY < 0) {
        currentDir= Direction::UP;
    }
    else if (moveY > 0) {
        currentDir = Direction::DOWN;
    }
    // If moving horizontally but not vertically, pick left/right
    if (moveX < 0) {
        currentDir = Direction::LEFT;
    }
    else if (moveX > 0) {
        currentDir = Direction::RIGHT;
    }
}

void Player::updateAnim()
{
    if(isMoving){
        currentAnim = AnimationState::WALK;
    }
    else{
        currentAnim = AnimationState::IDLE;
    }
}

