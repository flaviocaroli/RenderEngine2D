//Player.cpp


#include "Player.hpp"
#include <iostream>
#include <string>
#include "ResourceManager.hpp"


Player::Player(const std::string& texture_path,
               SDL_Renderer* renderer, int x, int y, int w, int h)
    : Entity("", renderer, x, y, w, h),
      moveX(0),
      moveY(0),
      baseSpeed(1),
      runSpeed(2),
      currentDir(Direction::DOWN),
      currentAnim(AnimationState::IDLE),
      isMoving(false),
      isRunning(false),
      isJumping(false),
      currentFrame(0),
      texture(nullptr),  
      frameWidth(64),
      frameHeight(64),
      frameTime(100),     
      lastFrameTick(0)

{   
    frameCount[0] = 1; // IDLE: 1 frame for each direction
    frameCount[1] = 6; // WALK: 6 frames for each direction
    frameCount[2] = 2; // RUN: 2 frames for each direction
    frameCount[3] = 4; // JUMP: 4 frames for each direction
    texture = ResourceManager::getTexture(texture_path, renderer);

    if(!texture){
        std::cerr << "Failed to load sprite" << texture_path << "\n";
    }
    
}

void Player::handleEvent(const SDL_Event& e) {
    // Key down (press)
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_w: moveY = -baseSpeed; break; // up
            case SDLK_a: moveX = -baseSpeed; break; // left
            case SDLK_s: moveY =  baseSpeed; break; // down
            case SDLK_d: moveX =  baseSpeed; break; // right


            //RUN 

            case SDLK_SPACE:
                // Only start running if already moving
                if (moveX != 0 || moveY != 0){
                    isRunning = true;
                    if (moveY <0){
                        moveY = -runSpeed;
                    }
                    else if (moveY > 0){
                        moveY = runSpeed;
                    }
                    else{
                        moveY = 0;
                    }
                    moveX = (moveX <0)? -runSpeed : (moveX > 0) ? runSpeed : 0;
                    //moveY = (moveY < 0) ? -runSpeed : (moveY > 0) ? runSpeed : 0;
                }
                break;

            case SDLK_j:
                // Only jump if moving and not already jumping
                if (moveX != 0 || moveY != 0 && !isJumping) {
                    isJumping = true;
                }
                break;
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
            
            case SDLK_SPACE: 
                isRunning = false;
                if (moveX != 0 ){
                    moveX = (moveX< 0) ? -baseSpeed : baseSpeed;
                }
                if (moveY != 0){
                    moveY = (moveY < 0) ? -baseSpeed: baseSpeed;
                }
                break;

            case SDLK_j:
                isJumping = false;
                break;

            default: break;
            
        }
    }
}


void Player::update() { //calculates the frame to use in the render function
    // Move according to velocity
    int currentSpeed = isRunning ? runSpeed : baseSpeed;
    x += moveX;
    y += moveY;

    //Movement animation logic
    isMoving = (moveX != 0 || moveY != 0);

    updateDir();
    updateAnim();
    
    Uint32 animSpeed = frameTime;  // default = 100
    if (currentAnim == AnimationState::RUN) {
        animSpeed = 150;           // run faster load of frames
    } 
    else{
        animSpeed = 100;
    }
    //Animation
    if (isMoving){
        Uint32 now = SDL_GetTicks(); // time in ms since SDL init
        //now - lastFrameTick is the amount of time that has passed since we last updated the animation frame
        if (now - lastFrameTick >= animSpeed) {
            //advance to next frame
            lastFrameTick = now;

            int total = frameCount[static_cast<int>(currentAnim)];
            
            currentFrame = (currentFrame + 1) % total; 
            // cycles 0->1->2->...->5->0->...
        }
    }
    if (!isMoving) {
        currentFrame = 0;
    }   
}

void Player::render(int cameraX, int cameraY){


    // Convert currentDirection to row index
    int rowIndex = static_cast<int>(currentDir);
    int colIndex = 0;
    
    // Adjust column based on animation state
    switch(currentAnim) {

        case AnimationState::IDLE:
            colIndex = 0;
            break;
        case AnimationState::WALK:
            colIndex = currentFrame;
            rowIndex += 4; // Walk animations start at row 4
            break;
            
        /* 
        case AnimationState::PUSH:
            colIndex = currentFrame;
            rowIndex += 0; // Push animations are in first set of rows
            break;
        case AnimationState::PULL:
            colIndex = currentFrame + 3; // Pull frames start after push frames
            rowIndex += 0;
            break; 
        */

        case AnimationState::JUMP:
            colIndex = currentFrame + 5; // Jump frames start after pull frames
            rowIndex += 0;
            break;
        case AnimationState::RUN:
            colIndex = currentFrame + 6;
            rowIndex += 4; // Run animations use walk rows but different frames
            break;
    }

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


    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
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
    if (!isMoving) {
        currentAnim = AnimationState::IDLE;
        return;
    }

    // Prioritize jumping over other states
    if (isJumping) {
        currentAnim = AnimationState::JUMP;
    } else if (isRunning) {
        currentAnim = AnimationState::RUN;
    } else {
        currentAnim = AnimationState::WALK;
    }
}

