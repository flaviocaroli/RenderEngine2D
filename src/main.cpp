#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;
    if(!game.init("Dream Frames", 1900, 1100)){
        return -1;
    }
    while(game.isRunning()){
        game.handleEvents();
        game.update();
        game.render();
    }    

    return 0;
}