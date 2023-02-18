#include "precompiled.hpp"
#include "Entity.hpp"

namespace TwilliEngine
{
Component* Entity::GetComponentByName(std::string_view name)
{
    auto it = std::find_if(mComponents.begin(), mComponents.end(),
                           [=](std::unique_ptr<Component>& component)
                           { return component->mName == name; });

    if (it == mComponents.end()) {
        err::LogError("Attempted to get component with name: ", name, " but it doesnt exist in entity: ", mName);
        return nullptr;
    }

    return it->get();
}

} // namespace TwilliEngine