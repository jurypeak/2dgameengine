#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <bitset>

class Entity;

#include "Component.h"
#include "Entity.h"
#include "Config.h"

// Processes entities that contains a signature.
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;
        
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        // Define component type that entities must have to be considered for the system.
        template <typename TComponent> void RequireComponent();
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.set(componentId);
}

#endif

