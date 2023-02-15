#include "precompiled.hpp"
#include "GraphicsSystem.hpp"


namespace TwilliEngine
{
GraphicsSystem::GraphicsSystem()
{
    D3D::Initialize();

    mWindow = std::make_unique<Window>();
    mSwapChain = std::make_unique<SwapChain>(mWindow->GetHandle());
}

GraphicsSystem::~GraphicsSystem() noexcept
{
    D3D::Shutdown();
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