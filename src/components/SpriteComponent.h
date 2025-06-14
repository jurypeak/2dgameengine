#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <cstddef>
#include <glm/glm.hpp>
#include <string>
#include <SDL.h>

struct SpriteComponent {
    std::string assetId;
    std::size_t width;
    std::size_t height;
    std::size_t zIndex;

    SDL_Rect srcRect;

    SpriteComponent(
        std::string assetId = "",
        std::size_t width = 0,
        std::size_t height = 0,
        // zIndex should be layers rather than just a number.
        std::size_t zIndex = 0,
        int srcRectX = 0,
        int srcRectY = 0
    ) {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, static_cast<int>(width), static_cast<int>(height)};
    }
};

#endif
