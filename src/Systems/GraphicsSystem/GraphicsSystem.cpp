#include "precompiled.hpp"
#include "GraphicsSystem.hpp"


namespace TwilliEngine
{
GraphicsSystem::GraphicsSystem()
{
        // Create Main Window
    try {
        mWindow = std::make_unique<Window>();
    }
    catch (std::exception ex) {
        err::Assert(true, "Unable to Create Main Window");
    }

        // Create Swapchain
    try {
        mSwapChain = std::make_unique<SwapChain>(mWindow->GetHandle());
    }
    catch (std::exception ex) {
        err::Assert(true, "Unable to Create SwapChain");
    }
}

GraphicsSystem::~GraphicsSystem()
{

}

void GraphicsSystem::StartFrame()
{
    mSwapChain->BindSwapChain();
}

void GraphicsSystem::Update(float )
{
}

void GraphicsSystem::EndFrame()
{
    mSwapChain->ClearSwapChain();
}

} // namespace TwilliEngine