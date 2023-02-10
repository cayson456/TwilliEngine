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

        // Create D3D
    try {
        mD3D = std::make_unique<D3D>();
    }
    catch (std::exception ex) {
        err::Assert(true, "Unable to Create D3D");
    }

        // Create Swapchain
    try {
        mSwapChain = std::make_unique<SwapChain>(mWindow->GetHandle(), mD3D->GetDevice(), mD3D->GetContext());
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
    mSwapChain->BindSwapChain(mD3D->GetContext());
}

void GraphicsSystem::Update(float )
{
}

void GraphicsSystem::EndFrame()
{
    mSwapChain->ClearSwapChain(mD3D->GetContext());
}

} // namespace TwilliEngine