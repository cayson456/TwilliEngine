#pragma once
#include "Systems/System.hpp"
#include "Window.hpp"
#include "SwapChain.hpp"

namespace TwilliEngine
{
class GraphicsSystem : public System
{
public:
    GraphicsSystem();
    ~GraphicsSystem();

    void StartFrame();
    void Update(float dt);
    void EndFrame();

private:
    std::unique_ptr<Window> mWindow;
    std::unique_ptr<SwapChain> mSwapChain;
};

} // namespace TwilliEngine