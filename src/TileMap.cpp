#include "TileMap.hpp"
#include "ResourceManager.hpp"
#include <SDL2/SDL.h>
#include <iostream>

TileMap::TileMap(SDL_Renderer* renderer, const std::string& tilesetFile, int tileWidth, int tileHeight)
    :renderer(renderer), tileset(nullptr), tileWidth(tileWidth), tileHeight(tileHeight), tilesetCols(0)
{
    tileset = ResourceManager::getTexture(tilesetFile, renderer);
    
    // Figure out how many columns the tileset has
    if (tileset) {
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(tileset, nullptr, nullptr, &texW, &texH);
        // Number of columns in the tileset
        tilesetCols = texW / tileWidth;
        std::cout << "texW=" << texW << ", texH=" << texH 
          << ", tileWidth=" << tileWidth 
          << ", tileHeight=" << tileHeight 
          << ", tilesetCols=" << tilesetCols << std::endl;

    }
}

void TileMap::loadMap(const std::vector<std::vector<int>>& mapData) {
    tiles = mapData;
}

void TileMap::render(int offsetX, int offsetY){
    if(!tileset){
        return;
    }
    // Go through each tile in 'tiles'
    for(int row; row < (int)tiles.size(); ++row) {
        for(int col; col < (int)tiles[row].size(); ++col) {
            int index = tiles[row][col];
            if(index < 0 ){
                continue; //skip empty or invalid 
            }
            // rectangle to draw
            int srcX = (index % tilesetCols) * tileWidth; 
            int srcY = (index / tilesetCols) * tileHeight;

            SDL_Rect srcRect { srcX, srcY, tileWidth, tileHeight};
            // destination rectangle on screen
            SDL_Rect dstRect {
                col* tileWidth,
                row * tileHeight,
                tileWidth,
                tileHeight
            };
            SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
        }
    }
}
