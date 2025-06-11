#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

class MovementSystem: public System {
    public:
        MovementSystem() {
            // TODO: 
            // RequireComponent<TransformComponent>();
        }

        void Update() {
            // TODO:
            // Loop all entities that the system is intrested in.
            for (auto entity: GetEntities()) {
                // Update entity pos based on velo
            }
        }
};

#endif
