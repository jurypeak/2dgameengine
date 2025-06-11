#ifndef COMPONENT_H
#define COMPONENT_H

struct IComponent {
    protected:
        static int nextId;
};

// Used to assign a unique id to a component type.
template<typename T>
class Component: public IComponent {
    static int GetId() {
        static auto id = nextId++;
        return id;
    }
};

#endif 
