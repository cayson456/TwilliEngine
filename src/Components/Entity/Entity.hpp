#pragma once
#include "Components/Component.hpp"

namespace TwilliEngine
{

// Container for resources
class Entity
{
public:
    Entity() {}
    Entity(std::string_view name) : mName(name) {}
    ~Entity() { mComponents.clear(); }

    template <typename T>
    T* AddComponent(std::string_view name = "Unnamed Component");

    template <typename T>
    T* GetComponent();

    Component* GetComponentByName(std::string_view name);

    std::string mName;

private:
    std::vector<std::unique_ptr<Component>> mComponents;

    // Static Stuff!
    // I KNOW EVERYTHING IS A GLOBAL... IT'S EASIER x.x
    //////////////////////////////////////
public:

    static void ReorganizeEntities();

    static Entity* FindEntityByName(std::string_view name);

    static void RemoveEntityByName(std::string_view name);
    static void RemoveAllEntites() { sEntities.clear(); }

    static const std::vector<std::unique_ptr<Entity>>& GetEntities() { return sEntities; }

    static Entity* CreateEntity(std::string_view name = "Unnamed Entity");

private:

        // it's a vector so we can iterate through every entity
        // allows for resorting for more effecient iterations
    static std::vector<std::unique_ptr<Entity>> sEntities;
};

} // namespace TwilliEngine

#include "Entity.inl"