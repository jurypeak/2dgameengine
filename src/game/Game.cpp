#include "Game.h"
#include "../logger/Logger.h"
#include <SDL.h>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Registry.h"
#include "../ecs/System.h"
#include <SDL_image.h>
#include <glm/glm.hpp>

Game::Game() {
    isRunning = false;
    Logger::Log("Game constructor called!");
}

Game::~Game() {
    Logger::Log("Game deconstructor called!");
}

void Game::Initialise() {
    if (SDL_Init(SDL_INIT_EVERYTHING) !=0) {
        Logger::Log("Error initialising SDL.");
        return;
    }
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = 800;//displayMode.w;
    windowHeight = 600;//;displayMode.h;
    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        Logger::Err("Error creating SDL window.");
        return;
    }
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!renderer) {
        Logger::Err("Error creating SDL renderer.");
        return;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    isRunning = true;
}

void Game::Run() {
    Setup();
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}


void Game::Setup() {

}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while(SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;
        }
    }
}

void Game::Update() {
    // If update is too fast, delay some time until MILLISECS_PER_FRAME is reached.
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreFrame); 
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait); // When there excess time give CPU time to process other processes outside the game.
    }

    // Diff in ticks since the last frame, converted to seconds.
    double deltaTime = (SDL_GetTicks() - millisecsPreFrame) / 1000.0;

    // Store previous frame time.
    millisecsPreFrame = SDL_GetTicks();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Presents the back buffer to the front, and swaps the previous front buffer to the back. Double-buffered render.
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
