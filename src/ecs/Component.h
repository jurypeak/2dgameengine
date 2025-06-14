#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstddef>

struct IComponent {
    protected:
        static std::size_t nextId;
};

// Used to assign a unique id to a component type.
template<typename T>
class Component: public IComponent {
    public:
        static std::size_t GetId() {
            static auto id = nextId++;
            return id;
        }
};

#endif 
