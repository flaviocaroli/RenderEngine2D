//TileMap.cpp


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
        /* debug print
        //  std::cout << "texW=" << texW << ", texH=" << texH 
        //  << ", tileWidth=" << tileWidth 
        //  << ", tileHeight=" << tileHeight 
        //  << ", tilesetCols=" << tilesetCols << std::endl;
        */
    }
}

void TileMap::loadMap(const std::vector<std::vector<int>>& mapData) {
    tiles = mapData;
}

int TileMap::getRows() const {
    // The number of rows is just the size of 'tiles'
    return (int)tiles.size();
}

int TileMap::getCols() const {
    return (int)tiles[0].size();
}

void TileMap::render(int offsetX, int offsetY){
    if(!tileset){
        return;
    }
    // Go through each tile in 'tiles'
    for(int row = 0; row < (int)tiles.size(); ++row) {
        for(int col = 0; col < (int)tiles[row].size(); ++col) {
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
                col* tileWidth - offsetX,
                row * tileHeight -offsetY,
                tileWidth,
                tileHeight
            };
            SDL_RenderCopy(renderer, tileset, &srcRect, &dstRect);
        }
    }
}
