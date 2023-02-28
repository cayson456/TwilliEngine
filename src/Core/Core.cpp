#include "precompiled.hpp"
#include "Core.hpp"

#include "Systems/GraphicsSystem/GraphicsSystem.hpp"
#include "Systems/WorldSystem/WorldSystem.hpp"

#include "Singletons/SwapChain/SwapChain.hpp"
#include "Singletons/Window/Window.hpp"

namespace TwilliEngine
{

bool Core::bRunning = true;

void Core::Run()
{
    D3D::Initialize();
    Window::Initialize();
    SwapChain::Initialize();

        // Must start and loop in a specific order
    StartSystem<WorldSystem>();
    StartSystem<GraphicsSystem>();

    while (bRunning)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                bRunning = false;
        }
        if (!bRunning)
            break;

        float dt = 0.016f;
        for (auto &sys : mSystems) {
            if (sys->IsEnabled())
            sys->StartFrame();
        }

        for (auto &sys : mSystems) {
            if (sys->IsEnabled())
            sys->Update(dt);
        }

        for (auto &sys : mSystems) {
            if (sys->IsEnabled())
            sys->EndFrame();
        }
    }
}

void Core::Shutdown()
{
    while (!mSystems.empty())
        mSystems.pop_back();

    SwapChain::Shutdown();
    D3D::Shutdown();
    Window::Shutdown();
}
} // namespace TwilliEngine