#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h> 
#include <string>
#include "TileMap.hpp"
#include "Player.hpp"
#include "CollisionManager.hpp"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    TileMap* tileMap;
    Player* player;


    //what to see according to player position
    int cameraX;
    int cameraY;

    CollisionManager collisionManager;

    // store these so we can reference them when resizing the Game Window
    static const int tileWidth  = 32;
    static const int tileHeight = 32;
    
public:
    Game();
    ~Game();

    bool init(const std::string& title, int width, int height);
    void handleEvents();
    void render();
    void clean();
    void update();

    bool isRunning() const {return running;}

    // Provide accessors
    SDL_Renderer* getRenderer() const { return renderer; }
    TileMap* getTileMap() const { return tileMap; }

    // The global list of entities (including the player)
    std::vector<Entity*> entities;
};
    
#endif