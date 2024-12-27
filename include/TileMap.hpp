#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TileMap  {
private:
    SDL_Renderer* renderer;
    SDL_Texture* tileset;
    int tileWidth;
    int tileHeight;
    int tilesetCols;

    std::vector<std::vector<int>> tiles;

public:
    TileMap(SDL_Renderer* renderer, const std::string& tilesetFile, int tileWidth, int tileHeight);
    ~TileMap() {}

    void loadMap(const std::vector<std::vector<int>>& mapData);
    void render(int offsetX, int offsetY);
};


#endif