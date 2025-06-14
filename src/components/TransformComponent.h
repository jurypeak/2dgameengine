#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec2 pos;
    glm::vec2 scale;
    double rotation;

    TransformComponent(glm::vec2 pos = glm::vec2(0, 0), glm::vec2 scale = glm::vec2 (1, 1), double rotation = 0.0) {
        this->pos = pos;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif
