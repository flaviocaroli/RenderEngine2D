#include "Game.hpp"
#include "ResourceManager.hpp"
#include <iostream>

// store these so we can reference them when resizing the Game Window
static const int tileWidth  = 32;
static const int tileHeight = 32;

Game::Game()
    :window(nullptr), renderer(nullptr), running(false), tileMap(nullptr)
{}

Game::~Game() {
    clean();
}

bool Game::init(const std::string& title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
        std::cerr << "SDL did not initialize" << SDL_GetError() << "\n";
        return false;
    } 
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); //to make the window resizable
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

    running = true;

    tileMap = new TileMap(renderer, "../assets/FieldsTileset.png", 32, 32);

    // At init, fill the map to match the initial window size
    int windowW = 0;
    int windowH = 0;
    SDL_GetWindowSize(window, &windowW, &windowH);

    int tilesWide = (windowW  + tileWidth  - 1) / tileWidth;  // round up
    int tilesHigh = (windowH + tileHeight - 1) / tileHeight; // round up


    // Build initial map data with 64 tiles.
    std::vector<std::vector<int>> mapData(tilesHigh, std::vector<int>(tilesWide));
    for (int row = 0; row < tilesHigh; ++row) {
        for (int col = 0; col < tilesWide; ++col) {
            mapData[row][col] = (row * tilesWide + col) % 64;
        }
    }

    tileMap->loadMap(mapData);
    return true;
    
}   

void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;

            //to resize window
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int newW = event.window.data1;
                    int newH = event.window.data2;

                    // Recalculate map size for the new window dimensions
                    int tilesWide = newW / tileWidth;
                    int tilesHigh = newH / tileHeight;

                    // Build new mapData and reload
                    std::vector<std::vector<int>> mapData(tilesHigh,
                                            std::vector<int>(tilesWide));
                    for (int row = 0; row < tilesHigh; ++row) {
                        for (int col = 0; col < tilesWide; ++col) {
                            mapData[row][col] = (row * tilesWide + col) % 64;
                        }
                    }
                    tileMap->loadMap(mapData);
                }
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
    SDL_SetRenderDrawColor(renderer, 50,50,50,255);
    SDL_RenderClear(renderer);

    //TODO : render game objects
    if(tileMap){
        tileMap->render(0, 0);
    }

    SDL_RenderPresent(renderer);

}

void Game::clean(){

    if(tileMap){ 
        delete tileMap;
        tileMap = nullptr;
    }

    //Destroy textures
    ResourceManager::clear();

    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}