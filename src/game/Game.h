#ifndef GAME_H // Guards for header file (Can also use #pragma once)
#define GAME_H

#include <SDL.h>
#include <memory>
    
#include "../ecs/Registry.h"
#include "../assetstore/AssetStore.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS; // Amount of millisecs allocated to each frame to process. 

class Game {
    private:
        bool isRunning;
        int millisecsPreFrame = 0;
        SDL_Window* window;
        SDL_Renderer* renderer;

        std::unique_ptr<Registry> registry;
        std::unique_ptr<AssetStore> assetStore;

    public:
        Game();
        ~Game();
        void Initialise();
        void Run();
        void Setup();
        void LoadLevel(int level);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();

        size_t windowWidth;
        size_t windowHeight;
};

#endif
