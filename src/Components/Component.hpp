#pragma once

namespace TwilliEngine
{
class Entity;

class Component
{
public:
    Component() : mOwner(nullptr) {}
    Component(std::string_view name) : mName(std::string(name)), mOwner(nullptr) {}
    virtual ~Component() {}

    std::string mName;

    Entity* GetOwner() { return mOwner; }

private:
    friend class Entity;

    Entity* mOwner;
};

} // namespace TwilliEngine

#include "Component.inl"