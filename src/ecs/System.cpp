#include "System.h"
#include "Entity.h"
#include <bits/stdc++.h>
#include <vector>

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

// Lambda function research it.
// Erase remove idiom.
void System::RemoveEntityFromSystem(Entity entity) {
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
        return entity == other;
    }), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}
