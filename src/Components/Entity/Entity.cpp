#include "precompiled.hpp"
#include "Entity.hpp"

namespace TwilliEngine
{

std::vector<std::unique_ptr<Entity>> Entity::sEntities =
    std::vector<std::unique_ptr<Entity>>();

    // NOTE: I KNOW I CAN JUST LOOP THROUGH IT NORMALLLY
    // am trying to learn how to do lamdas though
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

void Entity::ReorganizeEntities()
{
}

Entity* Entity::FindEntityByName(std::string_view name)
{
    auto it = std::find_if(sEntities.begin(), sEntities.end(),
                           [=](std::unique_ptr<Entity>& entity)
                           { return entity->mName == name; });

    if (it == sEntities.end()) {
        err::LogError("Attempted to find entity with name: ", name, " but it doesnt exist.");
        return nullptr;
    }

    return it->get();
}

void Entity::RemoveEntityByName(std::string_view name)
{
    sEntities.erase(std::remove_if(sEntities.begin(), sEntities.end(),
                    [=](const std::unique_ptr<Entity>& entity)
                    { return entity->mName == name; }));
}

Entity* Entity::CreateEntity(std::string_view name)
{
    sEntities.push_back(std::make_unique<Entity>(name));
    return sEntities.back().get();
}

} // namespace TwilliEngine