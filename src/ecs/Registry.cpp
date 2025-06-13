#include "Registry.h"
#include "System.h"
#include "Entity.h"
#include "../logger/Logger.h"

Entity Registry::CreateEntity() {
    int entityId;

    entityId = numEntities++;

    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);

    if (entityId >= entityComponentSignatures.size()) {
        entityComponentSignatures.resize(entityId + 1);
    }

    Logger::Log("Entity created with id = " + std::to_string(entityId));

    return entity;
}


// Adds the entity to all systems that are interested in it.
// A system is considered interested if the entity's component signature
// matches (i.e., includes) all the components the system requires.
void Registry::AddEntityToSystems(Entity entity) {
    const int entityId = entity.GetId();
    const auto& entityComponentSignature = entityComponentSignatures[entityId];

    for (auto& system : systems) {
        const auto& systemComponentSignature = system.second->GetComponentSignature();

        // A system is interested if all bits set in its signature are also set in the entity's signature.
        bool isIntrested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

        if (isIntrested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}


void Registry::Update() {
    // Add the entities that are waiting to be created to the active systems.
    for (auto entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();
}
