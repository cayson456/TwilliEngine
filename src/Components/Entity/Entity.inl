#include "Entity.hpp"

namespace TwilliEngine
{
template<typename T>
inline Component* Entity::AddComponent()
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(),
                           [](std::unique_ptr<Component>& component)
                           { return typeid(T) == typeid(component.get()); });

    if (it != mComponents.end()) {
        err::LogError("Attempted to add duplicate component of type ", typeid(T).name(), " in entity ", mName);
        return nullptr;
    }

    mComponents.push_back(std::move(std::make_unique<T>()));
    return mComponents.back().get();
}

template<typename T>
Component* Entity::AddComponent(std::string_view name)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(),
                           [](std::unique_ptr<Component>& component)
                           { return typeid(T) == typeid(component.get()); });

    if (it != mComponents.end()) {
        err::LogError("Attempted to add duplicate component of type ", typeid(T).name(), " in entity ", mName);
        return nullptr;
    }

    mComponents.push_back(std::move(std::make_unique<T>(name)));
    mComponents.back().get();
}

template<typename T>
Component* Entity::GetComponent()
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(), 
                           [](std::unique_ptr<Component>& component)
                           { return typeid(T) == typeid(component.get()); });

    if (it == mComponents.end()) {
        err::LogError("Attempted to get component of type: ", typeid(T).name(), " but it doesnt exist in entity: ", mName);
        return nullptr;
    }

    return it->get();
}
}