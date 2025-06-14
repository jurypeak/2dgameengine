#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent {
    glm::vec2 velo;

    RigidBodyComponent(glm::vec2 velo = glm::vec2(0.0, 0.0)) {
        this->velo = velo;
    }
};

#endif
