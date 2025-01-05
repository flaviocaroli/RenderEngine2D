#ifndef NPC_HPP
#define NPC_HPP

#include "Entity.hpp"
#include "Dialogue.hpp"

class NPC : public Entity{
    private:
        Dialogue dialogue;
    
    public:
        NPC(const std::string& texturePath, SDL_Renderer* renderer, int x, int y, int w, int h, const std::string& fontPath )
            :Entity(texturePath, renderer, x, y, w, h), dialogue(renderer, fontPath) {}
        
        Dialogue& getDialogue(){
            return dialogue;
        }

        void render(int cameraX, int cameraY) override{
            Entity::render(cameraX, cameraY);
            if (dialogue.isActive()){
                dialogue.render(getX(), getY(), getW(), getH(), cameraX, cameraY);
            }
        }
};

#endif