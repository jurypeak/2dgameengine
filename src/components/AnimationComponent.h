#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL.h>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLooped;
    int startTime;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLooped = true) {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLooped = isLooped;
        this->startTime = SDL_GetTicks();
    }
};

#endif 
