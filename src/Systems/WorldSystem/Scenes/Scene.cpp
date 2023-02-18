#include "precompiled.hpp"
#include "Scene.hpp"

namespace TwilliEngine
{
void Scene::ReorganizeEntities()
{
}
Entity* Scene::FindEntityByName(std::string_view name)
{
    auto it = std::find_if(mEntities.begin(), mEntities.end(),
                           [=](std::unique_ptr<Entity>& entity)
                           { return entity->mName == name; });

    if (it == mEntities.end()) {
        err::LogError("Attempted to find entity with name: ", name, " but it doesnt exist.");
        return nullptr;
    }

    return it->get();
}
void Scene::RemoveEntityByName(std::string_view name)
{
    mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(),
                    [=](const std::unique_ptr<Entity>& entity)
                    { return entity->mName == name; }));
}
} // namespace TwilliEngine