#pragma once
#include "Systems/WorldSystem/Scenes/Scene.hpp"


namespace TwilliEngine
{
class DefaultScene : public Scene
{
public:
    DefaultScene();
    ~DefaultScene();

    void StartFrame() override;
    void Update(float dt) override;
    void EndFrame() override;

private:
    Entity* mBunny;
    Entity* mCamera;
};

} // namespace TwilliEngine