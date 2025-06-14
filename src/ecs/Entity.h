#ifndef ENTITY_H
#define ENTITY_H

#include <utility>

class Registry;

class Entity {
    private:
        std::size_t id;

    public:
        Entity(std::size_t id): id(id) {};
        std::size_t GetId() const;
        
        // Operator overload.
        bool operator <(const Entity& other) const { return id < other.id; }
        Entity& operator = (const Entity& other) = default;
        bool operator ==(const Entity& other) const { return id == other.id; }

        template <typename TComponent, typename ...TArgs> void AddComponent(TArgs&& ...args);
        template <typename TComponent> void RemoveComponent();
        template <typename TComponent> bool HasComponent() const;
        template <typename TComponent> TComponent& GetComponent() const;

        Registry* registry;
};

/*
* Entity templates.
*/

#include "Registry.h"

template <typename TComponent, typename ...TArgs> 
void Entity::AddComponent(TArgs&& ...args) {
    registry->template AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent> 
void Entity::RemoveComponent() {
    registry->template RemoveComponent<TComponent>(*this);
}

template <typename TComponent> 
bool Entity::HasComponent() const {
    return registry->template HasComponent<TComponent>(*this);
}

template <typename TComponent> 
TComponent& Entity::GetComponent() const {
    return registry->template GetComponent<TComponent>(*this);
}

#endif
