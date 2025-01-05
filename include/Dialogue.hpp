#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Dialogue {
private:
    std::vector<std::string> lines; // Dialogue lines
    size_t currentLine;             // Current line index
    bool active;                    // Is the dialogue active?
    SDL_Renderer* renderer;         // SDL renderer
    SDL_Rect dialogueBox;           // Dialogue box position and size
    std::string fontPath;           // Path to the font

public:
    Dialogue(SDL_Renderer* renderer, const std::string& fontPath);

    void addLine(const std::string& line);
    void start();
    void next();
    void render(int characterX, int characterY, int characterW, int characterH, int cameraX, int cameraY);
    bool isActive() const;
};

#endif // DIALOGUE_HPP
