#include "precompiled.hpp"
#include "Core.hpp"

#include "Systems/GraphicsSystem/GraphicsSystem.hpp"
#include "Systems/WorldSystem/WorldSystem.hpp"

namespace TwilliEngine
{

bool Core::bRunning = true;

void Core::Run()
{
        // Must start and loop in a specific order
    StartSystem<GraphicsSystem>();
    StartSystem<WorldSystem>();

    while (bRunning)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

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
}
} // namespace TwilliEngine