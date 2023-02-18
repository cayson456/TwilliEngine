#pragma once
#include "Components/Entity/Entity.hpp"

namespace TwilliEngine {

class Scene
{
public:
    Scene() {}
    ~Scene() {}

    virtual void StartFrame() = 0;
    virtual void Update(float dt) = 0;
    virtual void EndFrame() = 0;

    void ReorganizeEntities();

    Entity* FindEntityByName(std::string_view name);

    void RemoveEntityByName(std::string_view name);
    void RemoveAllEntites() { mEntities.clear(); }

private:
    // it's a vector so we can iterate through every entity
    // allows for resorting for more effecient iterations
    std::vector<std::unique_ptr<Entity>> mEntities;
};



} // namespace TwilliEngine