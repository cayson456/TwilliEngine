#pragma once

namespace TwilliEngine {

class Scene
{
public:
    Scene() {}
    ~Scene() {}

    virtual void StartFrame() = 0;
    virtual void Update(float dt) = 0;
    virtual void EndFrame() = 0;

private:

};



} // namespace TwilliEngine