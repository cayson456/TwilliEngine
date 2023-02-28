#pragma once
#include "Systems/System.hpp"

#include "Scenes/Scene.hpp"
#include "ResourceLoader/ResourceLoader.hpp"

#include "DirectXTK/Keyboard.h"
#include "DirectXTK/Mouse.h"

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

    template <typename T>
    void LoadScene();

private:
    std::unique_ptr<Scene> mLoadedScene;
    std::unique_ptr<ResourceLoader> mResourceLoader;

    std::unique_ptr<DirectX::Mouse> mMouse;
    std::unique_ptr<DirectX::Keyboard> mKeyboard;

    void ImGuiDisplayResources();
};


template<typename T>
void WorldSystem::LoadScene()
{
    if (!std::is_base_of<Scene, T>()) {
        err::LogError("Error, attempted to load a scene when it's not a scene: ", typeid(T).name());
        return;
    }

    try {
        mLoadedScene = std::make_unique<T>();
    }
    catch (std::exception ex) {
        err::LogError("Error, unable to load scene: ", typeid(T).name());
        return;
    }
}

} // namespace TwilliEngine