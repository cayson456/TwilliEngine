#pragma once
#include "Systems/System.hpp"

namespace TwilliEngine
{
class GraphicsSystem : public System
{
public:
    GraphicsSystem();
    ~GraphicsSystem() noexcept;

    void StartFrame();
    void Update(float dt);
    void EndFrame();

private:
    void InitializeImGui();
    void ShutdownImGui();

    void DrawAllEntities();
};

} // namespace TwilliEngine