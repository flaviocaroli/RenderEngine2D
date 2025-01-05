//Game.cpp

#include "Game.hpp"
#include <iostream>

Game::Game()
    :window(nullptr),
     renderer(nullptr),
     running(false), 
     tileMap(nullptr),
     player(nullptr),
     cameraX(0),
     cameraY(0)
{}

Game::~Game() {
    clean();
}

bool Game::init(const std::string& title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0) {
        std::cerr << "SDL did not initialize" << SDL_GetError() << "\n";
        return false;
    } 

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf did not initialize: " << TTF_GetError() << "\n";
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

    tileMap = new TileMap(renderer, "../assets/world/FieldsTileset.png", 32, 32);

    // At init, fill the map to match the initial window size
    int windowW = 0;
    int windowH = 0;
    SDL_GetWindowSize(window, &windowW, &windowH);

    int tilesWide = ((windowW + tileWidth  - 1) / tileWidth);  // round up
    int tilesHigh = ((windowH + tileHeight - 1) / tileHeight); // round up


    // Build initial map data with 64 tiles.
    std::vector<std::vector<int>> mapData(tilesHigh, std::vector<int>(tilesWide));
    for (int row = 0; row < tilesHigh; ++row) {
        for (int col = 0; col < tilesWide; ++col) {
            mapData[row][col] = (row * tilesWide + col) % 64;
        }
    }

    tileMap->loadMap(mapData);

    // Create the player at some position in world space (e.g., near top-left).
    // We'll assume each player sprite is also 32x32 for simplicity.
    player = new Player("../assets/player/Unarmed_Idle.png",
                        "../assets/player/Unarmed_Walk.png",
                        renderer, 50, 50, 128, 128);  

    // add elements to the map
    NPC* orc1 = new NPC("../assets/NPCs/orc1_idle.png", renderer, 230, 160, 128, 128, "../assets/utils/MovistarFont.ttf");
    NPC* orc2 = new NPC("../assets/NPCs/orc2_idle.png", renderer, 380, 160, 128, 128, "../assets/utils/MovistarFont.ttf");
    NPC* orc3 = new NPC("../assets/NPCs/orc3_idle.png", renderer, 530, 160, 128, 128, "../assets/utils/MovistarFont.ttf");

    orc1->getDialogue().addLine("Hello, traveler!");
    orc2->getDialogue().addLine("Beware of the dangers ahead.");
    orc3->getDialogue().addLine("Good luck on your journey!");
    ResourceManager::addNPC(orc1);
    ResourceManager::addNPC(orc2); 
    ResourceManager::addNPC(orc3);

    ResourceManager:: addPlayer(player);
    
    ResourceManager::addStaticEntity("../assets/world/Tree1.png", renderer, 100, 32, 256, 256);

    ResourceManager::addStaticEntity("../assets/world/Christmas_tree1.png", renderer, 250, 32, 256, 256);

    ResourceManager::addStaticEntity("../assets/world/Flower_tree1.png", renderer, 400, 32, 256, 256);
    
    


    return true;

}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            // Handle key presses
            case SDL_KEYDOWN: {
                if (player) {
                    // Let the player handle movement (WASD, arrow keys, etc.)
                    player->handleEvent(event);

                    // --- INTERACTIONS WITH THE WORLD ---

                    // 1) Start dialogue if E is pressed
                    if (event.key.keysym.sym == SDLK_e) {      
                        SDL_Rect box = {
                            player->getX() + 48,
                            player->getY() + 96,
                            player->getW() - 96,
                            player->getH() - 96
                        };

                        // Check collision with any entity
                        bool collide = collisionManager.hasCollision(
                            box,
                            tileMap,
                            ResourceManager::getEntities(),
                            player
                        );

                        if (collide) {
                            Entity* entity = collisionManager.getCollidingEntity(
                                box,
                                ResourceManager::getEntities(),
                                player
                            );
                            NPC* npc = dynamic_cast<NPC*>(entity);
                            if (npc) {
                                npc->getDialogue().start();
                            }
                        }
                    }
                    // 2) Advance dialogue if SPACE is pressed
                    else if (event.key.keysym.sym == SDLK_SPACE) {
                        // If any NPC currently has active dialogue, move to the next line
                        for (auto& entity : ResourceManager::getEntities()) {
                            NPC* npc = dynamic_cast<NPC*>(entity);
                            if (npc && npc->getDialogue().isActive()) {
                                npc->getDialogue().next();
                            }
                        }
                    }
                }
            } break;

            // Handle key releases
            case SDL_KEYUP: {
                if (player) {
                    // Let the player handle key release logic (e.g. stopping movement)
                    player->handleEvent(event);
                }
            } break;

            // Handle window events (like resizing)
            case SDL_WINDOWEVENT: {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    int newW = event.window.data1;
                    int newH = event.window.data2;

                    // Recalculate how many tiles fit in the new window
                    int tilesWide = newW / tileWidth;
                    int tilesHigh = newH / tileHeight;

                    // Build new map data and reload
                    std::vector<std::vector<int>> mapData(
                        tilesHigh,
                        std::vector<int>(tilesWide)
                    );
                    for (int row = 0; row < tilesHigh; ++row) {
                        for (int col = 0; col < tilesWide; ++col) {
                            mapData[row][col] = (row * tilesWide + col) % 64;
                        }
                    }
                    tileMap->loadMap(mapData);
                }
            } break;

            default:
                break;
        }
    }
}

void Game::update(){
    // Logic updates (Character mmovements, collisions, camera)
    
    if(player) {

        //collision handling
        int oldX = player->getX();
        int oldY = player->getY();
        
        player->update();
        //adjust box to get more granular collision
        SDL_Rect box = {player->getX() +48, player->getY() +96,
                          player->getW() -96, player->getH() -96};
        bool collide = collisionManager.hasCollision(box, tileMap, ResourceManager::getEntities(), player);
        if (collide){

            player->setX(oldX);
            player->setY(oldY);

        }

        //camera movement
        int windowW = 0, windowH = 0;
        SDL_GetWindowSize(window, &windowW, &windowH);
        //center camera on the player
        cameraX = player->getX() - (windowW /2) + 16;
        cameraY = player->getY() - (windowH /2) + 16;
        //clamp camera so it doesn't go beyond the map edges

        int tilesWide = ((windowW + tileWidth  - 1) / tileWidth);  // round up
        int tilesHigh = ((windowH + tileHeight - 1) / tileHeight); // round up
        int mapWidth  = tilesWide  * tileWidth;
        int mapHeight = tilesHigh  * tileHeight;

        if (cameraX < 0) {
            cameraX = 0;
        }
        if (cameraY < 0){
            cameraY = 0;
        }
        if (cameraX > mapWidth  - windowW){
            cameraX = mapWidth - windowW;
        }
        if (cameraY > mapHeight  - windowH){
            cameraY = mapHeight - windowH;
        }
    }
}

void Game::render(){
    //clear Screen
    SDL_SetRenderDrawColor(renderer, 50,50,50,255);
    SDL_RenderClear(renderer);

    //TODO : render game objects
    if(tileMap){
        tileMap->render(cameraX, cameraY);
    }

    // Render all entities
    for (auto& e : ResourceManager::getEntities()) {
        e->render(cameraX, cameraY);
    }

    SDL_RenderPresent(renderer);

}

void Game::clean(){

    if(tileMap){ 
        delete tileMap;
        tileMap = nullptr;
    }

    //Destroy textures and entities
    ResourceManager::clear();

    if(renderer){
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if(window){
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}