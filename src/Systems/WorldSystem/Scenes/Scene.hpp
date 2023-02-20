#pragma once
#include "Components/Entity/Entity.hpp"

namespace TwilliEngine {

class Scene
{
public:
    Scene() {}
    ~Scene() { Entity::RemoveAllEntites(); }

    virtual void StartFrame() = 0;
    virtual void Update(float dt) = 0;
    virtual void EndFrame() = 0;

private:

};



} // namespace TwilliEngine