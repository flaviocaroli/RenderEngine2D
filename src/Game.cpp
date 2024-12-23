#include "Game.hpp"
#include <iostream>

Game::Game()
    :window(nullptr), renderer(nullptr), running(false)
{}

Game::~Game() {
    clean();
}

bool Game::init(std::string& title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
        std::cerr << "SDL did not initialize" << SDL_GetError() << "\n";
        return false;
    } 
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (!window){
        std::cerr <<"SDL did not create window"<<SDL_GetError() << "\n";
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        std::cerr << "Renderer Not working" << SDL_GetError() <<"\n";
        return false;
    }
    running =true;
    return true;

}   
void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            default: 
                break;
        }
    }
}

void Game::update(){
    // Logic updates (NPc mmovements, physics, etc)
}

void Game::render(){
    //clear Screen
    SDL_SetRenderDrawColor(renderer, 50,50,50,255):
    SDL_RenderClear(renderer);

    //TODO : render game objects

    SDL_RenderPresent(renderer);

}

void Game::clean(){
    if(renderer){
        SDL_DestroyRenderer();
        renderer = nullptr;
    }
    if(window){
        SDL_DestroyWindow();
        window = nullptr;
    }

    SDL_Quit();
}