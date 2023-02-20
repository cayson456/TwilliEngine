#include "precompiled.hpp"
#include "WorldSystem.hpp"

#include "Scenes/DefaultScene/DefaultScene.hpp"
#include "imgui/imgui.h"

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
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    if (mLoadedScene)
        mLoadedScene->Update(dt);
}
void WorldSystem::EndFrame()
{
    if (mLoadedScene)
        mLoadedScene->EndFrame();
}

void WorldSystem::ImGuiDisplayResources()
{

}

} // namespace TwilliEngine