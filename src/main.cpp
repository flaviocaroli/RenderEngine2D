#include <iostream>
#include <SDL2/SDL.h>
#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;
    if(!game.init("Frammenti di Sogno", 600, 600)){
        return -1;
    }
    while(game.isRunning()){
        game.handleEvents();
        game.update();
        game.render();
    }    

    return 0;
}