#pragma once

namespace TwilliEngine
{

class Component
{
public:
    Component() {}
    Component(const std::string& name) : mName(name) {}
    ~Component() {}

    std::string mName;

private:
    

};
} // namespace TwilliEngine

#include "Component.inl"