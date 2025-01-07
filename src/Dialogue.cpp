#include "Dialogue.hpp"
#include <iostream>

Dialogue::Dialogue(SDL_Renderer* renderer, const std::string& fontPath)
    : currentLine(0), active(false), renderer(renderer), fontPath(fontPath) {
    dialogueBox = {0, 0, 200, 100}; // Default box size; will be repositioned per character
}

void Dialogue::addLine(const std::string& line) {
    lines.push_back(line);
}

void Dialogue::start() {
    if (!lines.empty()) {
        active = true;
        currentLine = 0;
    }
}

void Dialogue::next() {
    if (active) {
        if (currentLine + 1 < lines.size()) {
            currentLine++;
        } else {
            active = false;
        }
    }
}

void Dialogue::render(int characterX, int characterY, int characterW, int characterH, int cameraX, int cameraY) {
    if (!active || lines.empty()) {
        return;
    }

    // Calculate dialogue box position relative to character
    dialogueBox.x = characterX - cameraX + (characterW / 2) - (dialogueBox.w / 2);
    dialogueBox.y = characterY - cameraY - dialogueBox.h - 10;
    //debug variables
    //dialogueBox.x = 200;
    //dialogueBox.y = 200;
    

    // dialogue box
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White box
    SDL_RenderFillRect(renderer, &dialogueBox);

    // load font with its dimension
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 20);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Render text
    SDL_Color textColor = {0, 0, 0, 255}; // Black text
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, lines[currentLine].c_str(), textColor, dialogueBox.w -10);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Position text within the dialogue box
    SDL_Rect textRect = {dialogueBox.x + 10, dialogueBox.y + 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // Cleanup
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

bool Dialogue::isActive() const {
    return active;
}
