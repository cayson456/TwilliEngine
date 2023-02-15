#pragma once
#include "Systems/System.hpp"

#include "ResourceLoader.hpp"

namespace TwilliEngine
{
class WorldSystem : public System
{
public:
    WorldSystem();
    ~WorldSystem() noexcept;

    void StartFrame();
    void Update(float dt);
    void EndFrame();

private:
    std::unique_ptr<ResourceLoader> mResourceLoader;
    
};

} // namespace TwilliEngine