#ifndef POOL_H
#define POOL_H

#include <cstddef>
#include <vector>

class IPool {
    public:
        virtual ~IPool() {}
};

template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(std::size_t size = 100) {
        data.resize(size);
    }

    virtual ~Pool() = default;

    bool isEmpty() const {
        return data.empty();
    }

    std::size_t GetSize() const {
        return data.size();
    }

    void Resize(std::size_t n) {
        data.resize(n);
    }

    void Clear() {
        data.clear();
    }

    void Add(T object) {
        data.push_back(object);
    }

    void Set(std::size_t index, T object) {
        data[index] = object;
    }

    T& Get(std::size_t index) {
        return static_cast<T&>(data[index]);
    }

    T& operator [](std::size_t index) {
        return data[index];
    }
};

#endif
