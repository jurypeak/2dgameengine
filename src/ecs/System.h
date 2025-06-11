#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>
#include "Entity.h"
#include "Component.h"
#include <vector>

/* 
 * A bitset (1 and 0s) to keep track of which components
 * an entity has, and also helps keep track of which
 * entities a system is intrested in.
*/

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature ;

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

