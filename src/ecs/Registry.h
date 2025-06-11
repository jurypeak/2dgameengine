#ifndef REGISTRY_H
#define REGISTRY_H

#include "Pool.h"

// Manages the creation and destruction of entities, add systems, and components.
class Registry {
    private:
        // Keep track of how many entities were added to the scene.
        int numEntities = 0;
        
        // Vector of component pools, each pool contains all the data for a certain component type.
        // Vector index = component id.
        // Pool index = entity id.
        std::vector<IPool*> componentPools;
};

#endif
