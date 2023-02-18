#include "precompiled.hpp"
#include "GraphicsSystem.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "Singletons/SwapChain/SwapChain.hpp"
#include "Singletons/Window/Window.hpp"

namespace TwilliEngine
{
GraphicsSystem::GraphicsSystem()
{
    InitializeImGui();
}

GraphicsSystem::~GraphicsSystem() noexcept
{
    ShutdownImGui();
}

void GraphicsSystem::StartFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void GraphicsSystem::Update(float )
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
}

void GraphicsSystem::EndFrame()
{
    ImGui::Render();
    SwapChain::GetInstance()->BindSwapChain();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    SwapChain::GetInstance()->Present();
    SwapChain::GetInstance()->ClearSwapChain();
}

void GraphicsSystem::InitializeImGui()
{

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(Window::GetInstance()->GetHandle());
    ImGui_ImplDX11_Init(D3D::GetInstance()->GetDevice(), D3D::GetInstance()->GetContext());

}

void GraphicsSystem::ShutdownImGui()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();
}

} // namespace TwilliEngine