#ifndef REGISTRY_H
#define REGISTRY_H

#include "Component.h"
#include "Entity.h"
#include "Pool.h"
#include "System.h"
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <set>
#include <utility>

// Forward declarations
class Entity;
class IPool;
class System;

// Manages the creation and destruction of entities, add systems, and components.
class Registry {
    private:
        // Keep track of how many entities were added to the scene.
        int numEntities = 0;
        
        // Vector of component pools, each pool contains all the data for a certain component type.
        // [vector index = component id]
        // [pool index = entity id]
        std::vector<std::shared_ptr<IPool>> componentPools;

        // Vector of component signatures
        // The signature lets us know which components are turned "on" for an enitity.
        // [vector index = entity id]
        std::vector<Signature> entityComponentSignatures;

        // Map of active systems [index = system typeid]
        // Basically a dictionary but its all unsorted.
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

        // Set of entities that are flagged to be added or removed in the next registry Update().
        std::set<Entity> entitiesToBeAdded;
        std::set<Entity> entitiesToBeKilled;
    
    public:
        Registry() {

        }

        ~Registry() {

        }

        // Entity management
        Entity CreateEntity();
    
        // Component management 
        template <typename TComponent, typename ...TArgs> void AddComponent(Entity entity, TArgs&& ...args);
        template <typename TComponent> void RemoveComponent(Entity entity);
        template <typename TComponent> bool HasComponent(Entity entity) const;

        // System management
        template <typename TSystem, typename ...TArgs> void AddSystem(TArgs&& ...args);
        template <typename TSystem> void RemoveSystem();
        template <typename TSystem> bool HasSystem() const;
        template <typename TSystem> TSystem& GetSystem() const;

        // Checks the component signature of an entity and adds the entity to the systems,
        // that are intrested in it. 
        void AddEntityToSystems(Entity entity);
        

        // The registry Update() finally processes the entities that are waiting to be added or removed from the system.
        void Update();
};

/*
* Component Templates...
*/

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    // If the component id is > than the current size of the componentPools, then resize the vector.
    if (componentId >= componentPools.size()) {
        componentPools.resize(componentId + 1, nullptr);
    }

    // If no pool for the component type, create a new one.
    if (!componentPools[componentId]) {
        std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    // Get the pool of the type component.
    std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    // If the entity id is > than the pool size, resize the pool.
    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numEntities);
    }

    // Create the new component type by forwarding the parameters to the constructor.
    TComponent newComponent(std::forward<TArgs>(args)...);

    // Add the component to the component pool list, using the entity id as index.
    componentPool->Set(entityId, newComponent);

    // Change the signature of the entity and set the new component id on the bitset to "on" or "1".
    entityComponentSignatures[entityId].set(componentId);
}

// Removes the component from the entity by clearing its bit in the signature.
template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignatures[entityId].set(componentId, false); 
}

// Returns true if the bit corresponding to the component type is set in the entity's signature.
template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignatures[entityId].test(componentId); 
}

/*
* System Templates...
*/ 

// Adds a new system to the systems map using its type as the key.
template <typename TSystem, typename ...TArgs> 
void Registry::AddSystem(TArgs&& ...args) {
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

// Removes the system from the systems map using its type as the key.
template <typename TSystem> 
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

// Returns true if the system of the specified type exists in the systems map.
template <typename TSystem> 
bool Registry::HasSystem() const {
   return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

// Retrieves a reference to the system of the specified type from the systems map.
template <typename TSystem> 
TSystem& Registry::GetSystem() const {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

#endif
