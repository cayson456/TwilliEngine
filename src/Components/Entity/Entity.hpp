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
    Component* AddComponent();
    template <typename T>
    Component* AddComponent(std::string_view name);

    template <typename T>
    Component* GetComponent();
    Component* GetComponentByName(std::string_view name);

    std::string mName;

private:
    std::vector<std::unique_ptr<Component>> mComponents;

};

} // namespace TwilliEngine

#include "Entity.inl"