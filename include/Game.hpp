#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h> 
#include <string>
#include "TileMap.hpp"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    TileMap* tileMap;

public:
    Game();
    ~Game();

    bool init(const std::string& title, int width, int height);
    void handleEvents();
    void render();
    void clean();
    void update();

    bool isRunning() const {return running;}
};
    
#endif