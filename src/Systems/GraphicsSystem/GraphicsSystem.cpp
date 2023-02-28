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
    SwapChain::GetInstance()->ClearSwapChain();
    SwapChain::GetInstance()->BindSwapChain();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void GraphicsSystem::Update(float )
{

}

void GraphicsSystem::EndFrame()
{
    ImGui::EndFrame();
    
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    
    SwapChain::GetInstance()->Present();
    
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


void GraphicsSystem::DrawAllEntities()
{
 
}

} // namespace TwilliEngine