#include "precompiled.hpp"
#include "WorldSystem.hpp"

#include "Scenes/DefaultScene/DefaultScene.hpp"

namespace TwilliEngine
{
WorldSystem::WorldSystem()
{
    mResourceLoader = std::make_unique<ResourceLoader>();

    mResourceLoader->LoadAllAssetsInFolder();

    LoadScene<DefaultScene>();
}

WorldSystem::~WorldSystem() noexcept
{
    mResourceLoader->UnloadAllAssets();
}

void WorldSystem::StartFrame()
{
    if (mLoadedScene)
        mLoadedScene->StartFrame();
}

void WorldSystem::Update(float dt)
{
    if (mLoadedScene)
        mLoadedScene->Update(dt);
}
void WorldSystem::EndFrame()
{
    if (mLoadedScene)
        mLoadedScene->EndFrame();
}

} // namespace TwilliEngine