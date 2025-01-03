#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <string>
#include <vector> 
#include <array>

//since i have a file with 4 rows for sprites
enum class Direction {
    DOWN = 0,
    LEFT = 1,
    RIGHT = 2, 
    UP = 3,
};

enum class AnimationState{
    IDLE,
    WALK,
    //In future can add run, fight etc
};

class Player : public Entity {
private:
    int moveX;
    int moveY;
    int speed;

    //animation logic
    Direction currentDir;
    AnimationState currentAnim;
    bool isMoving;

    // The two textures
    SDL_Texture* idleTexture;
    SDL_Texture* walkTexture;
    

    int currentFrame;
    std::array<int, 2> frameCount; //how many frames per implemented animations
    int frameWidth;
    int frameHeight;

    Uint32 frameTime;      // is how many milliseconds to wait before moving on to the next animation frame.
    Uint32 lastFrameTick;  // stores milliseconds when the last frame change happened.

    //helper
    void updateDir();
    void updateAnim();

public:
    Player(const std::string& idle_path,
           const std::string& walk_path,
           SDL_Renderer* renderer, int x, int y, int w, int h);
    void handleEvent(const SDL_Event& e);
    void update() override; // update based on velocity
    void render(int cameraX, int cameraY) override;
};

#endif

