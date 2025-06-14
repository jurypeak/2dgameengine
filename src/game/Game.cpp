#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <memory>
#include <glm/glm.hpp>

#include "Game.h"
#include "../logger/Logger.h"
#include "../ecs/Entity.h"
#include "../ecs/System.h"
#include "../components/RigidBodyComponent.h"
#include "../components/TransformComponent.h"
#include "../systems/MovementSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/AnimationSystem.h"
#include "../components/AnimationComponent.h"
#include "SDL_video.h"

Game::Game() {
    isRunning = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    Logger::Log("Game constructor called!");
}

Game::~Game() {
    Logger::Log("Game deconstructor called!");
}

void Game::Initialise() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Log("Error initializing SDL.");
        return;
    }

    windowWidth = 1024;
    windowHeight = 768;

    // Create window (not fullscreen yet)
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN // NOT fullscreen or borderless here
    );

    if (!window) {
        Logger::Err("Error creating SDL window.");
        return;
    }

    // Set desired display mode (resolution)
    SDL_DisplayMode displayMode;
    displayMode.w = windowWidth;
    displayMode.h = windowHeight;
    displayMode.format = 0;
    displayMode.refresh_rate = 0;
    displayMode.driverdata = 0;

    if (SDL_SetWindowDisplayMode(window, &displayMode) != 0) {
        Logger::Err("Failed to set display mode");
        return;
    }

    // Now set fullscreen
    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
        Logger::Err("Failed to set fullscreen mode");
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        Logger::Err("Error creating SDL renderer.");
        return;
    }

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

void Game::LoadLevel(int level) {
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();

    assetStore->AddTexture(renderer, "tank-image", "./assets/images/tank-panther-right.png");
    assetStore->AddTexture(renderer, "truck-image", "./assets/images/truck-ford-right.png");
    assetStore->AddTexture(renderer, "jungle-map", "./assets/tilemaps/jungle.png");
    assetStore->AddTexture(renderer, "helicopter-image", "./assets/images/chopper.png");
    assetStore->AddTexture(renderer, "radar-image", "./assets/images/radar.png");

    // Load the tilemap from .map file (csv file).
    // Could find a better way of doing this.
    int tileSize = 32;
    double tileScale = 2;
    int mapNumCols = 25;
    int mapNumRows = 20;

    std::fstream mapFile;
    mapFile.open("./assets/tilemaps/jungle.map");

    for (int y = 0; y < mapNumRows; y++) {
        for (int x = 0; x <mapNumCols; x++) {
            char ch;
            mapFile.get(ch);
            int srcRectY = std::atoi(&ch) * tileSize;
            mapFile.get(ch);
            int srcRectX = std::atoi(&ch) * tileSize;
            // Ignores comma.
            mapFile.ignore();

            Entity tile = registry->CreateEntity();
            tile.AddComponent<TransformComponent>(
                glm::vec2(x * (tileScale * tileSize),
                y * (tileScale * tileSize)), 
                glm::vec2(tileScale, tileScale),
                0.0
            );
            tile.AddComponent<SpriteComponent>("jungle-map", tileSize, tileSize, 0, srcRectX, srcRectY);
        }
    }
    mapFile.close();

    Entity helicopter = registry->CreateEntity();
    helicopter.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(2.0, 2.0), 0.0);
    helicopter.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    helicopter.AddComponent<SpriteComponent>("helicopter-image", 32, 32, 2);
    helicopter.AddComponent<AnimationComponent>(2, 15, true);

    Entity radar = registry->CreateEntity();
    radar.AddComponent<TransformComponent>(glm::vec2(windowWidth - 74, 10.0), glm::vec2(1.0, 1.0), 0.0);
    radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 2);
    radar.AddComponent<AnimationComponent>(8, 5, true);

    Entity tank = registry->CreateEntity();
    tank.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(2.0, 2.0), 0.0);
    tank.AddComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));
    tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 2);

    Entity truck = registry->CreateEntity();
    truck.AddComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(2.0, 2.0), 0.0);
    truck.AddComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
    truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1); 
}

void Game::Setup() {
    LoadLevel(1);
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

    // Ask all the systems to update.
    registry->GetSystem<MovementSystem>().Update(deltaTime);
    registry->GetSystem<AnimationSystem>().Update();

    // Update the registry to process the entites that are waiting to be created/killed.
    registry->Update();
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    registry->GetSystem<RenderSystem>().Update(renderer, assetStore);

    // Presents the back buffer to the front, and swaps the previous front buffer to the back. Double-buffered render.
    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
