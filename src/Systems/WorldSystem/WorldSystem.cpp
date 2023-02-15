#include "precompiled.hpp"
#include "WorldSystem.hpp"


namespace TwilliEngine
{
WorldSystem::WorldSystem()
{
    mResourceLoader = std::make_unique<ResourceLoader>();

    mResourceLoader->LoadAllAssetsInFolder();
}

WorldSystem::~WorldSystem() noexcept
{

}

void WorldSystem::StartFrame()
{
}
void WorldSystem::Update(float)
{
}
void WorldSystem::EndFrame()
{
}
} // namespace TwilliEngine