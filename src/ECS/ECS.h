#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <set>
#include <unordered_map>
#include <typeindex>

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
    static int nextId;
};

template <typename T>
class Component : public IComponent
{
    static int GetId()
    {
        static auto id = nextId++;
        return id;
    };
};

class Entity
{
private:
    int id;

public:
    Entity(int id) : id(id) {};
    Entity(const Entity &entity) = default;
    int GetId() const;

    Entity &operator=(const Entity &other) = default;
    bool operator==(const Entity &other) const
    {
        return id == other.id;
    }

    bool operator!=(const Entity &other) const
    {
        return id != other.id;
    }
};

// System processes entities that contain a specific signature
class System
{
private:
    Signature componentSignature;
    std::vector<Entity> entities;

public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);

    std::vector<Entity> GetSystemEntities() const;
    const Signature &GetComponentSignature() const;

    template <typename TComponent>
    void RequireComponent();
};
// Just a vector that of objects type T

class IPool
{
public:
    virtual ~IPool() {}
};
template <typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;

public:
    Pool(int size = 100)
    {
        data.resize(size);
    }

    virtual ~Pool() = default;

    bool isEmpty() const
    {
        return data.empty();
    }

    int GetSize() const
    {
        return data.size();
    }

    void Resize(int n)
    {
        data.resize(n);
    }

    void Clear()
    {
        data.clear();
    }

    void Add(T object)
    {
        data.push_back(object);
    }

    void Set(int index, T object)
    {
        data[index] = object;
    }

    T &Get(int index)
    {
        return static_cast<T &>(data[index]);
    }

    T &operator[](unsigned int index)
    {
        return data[index];
    }
};
// The registry manages the creation and destruction of entities, add systems and components
class Registry
{
private:
    int numEntities = 0;

    // Vector of component tools, each pool contains all the data for certain component
    std::vector<IPool *> componentPools;

    // Vector of component signatures per entity
    std::vector<Signature> entityComponentSignature;

    std::unordered_map<std::type_index, System *> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeKilled;

public:
    Registry() = default;

    void Update();

    Entity CreateEntity();

    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs &&...args)
    {
    }
    // void AddEntityToSystem(Entity entity);
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto componentId = Component<TComponent>::GetId();
    componentSignature.setId(componentId);
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs &&...args)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = entity.GetId();

    if (componentId >= componentPools.size())
    {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])
    {
        Pool<TComponent> *newComponentPool = new Pool<TComponent>();
        componentPools[componentId] = newComponentPool;
    }

    Pool<TComponent> *componentPool = componentPools[componentId];

    if (entityId >= componentPool->GetSize())
    {
        componentPool->Resize(numEntities);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
}
#endif