#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class System;

#include "../ecs/System.h"
#include "../components/TransformComponent.h"
#include "../components/RigidBodyComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            // TODO: 
            RequireComponent<TransformComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void Update(double deltaTime) {
            // TODO:
            // Loop all entities that the system is intrested in.
            for (auto entity: GetSystemEntities()) {
                // Update entity position based on velocity
                auto& transform = entity.GetComponent<TransformComponent>();
                const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

                transform.pos.x += rigidbody.velo.x * deltaTime;
                transform.pos.y += rigidbody.velo.y * deltaTime;
            }
        }
};

#endif
