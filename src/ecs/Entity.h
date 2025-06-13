#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id) {};
        int GetId() const;
        
        // Operator overload.
        bool operator <(const Entity& other) const { return id < other.id; }
        Entity& operator = (const Entity& other) = default;
        bool operator ==(const Entity& other) const { return id == other.id; }
};

#endif
