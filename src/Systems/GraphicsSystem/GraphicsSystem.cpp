#include "precompiled.hpp"
#include "GraphicsSystem.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "Singletons/SwapChain/SwapChain.hpp"
#include "Singletons/Window/Window.hpp"

#include "Components/Entity/Entity.hpp"
#include "Components/GraphicsComponent/GraphicsComponent.hpp"
#include "Components/TransformComponent/TransformComponent.hpp"
#include "Components/CameraComponent/CameraComponent.hpp"

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
    DrawAllEntities();
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


void GraphicsSystem::DrawAllEntities()
{
    // Search for camera. Should be reorganized to be the first entity.
    Entity* camera_entity = nullptr;
    CameraComponent* camera_cmp = nullptr;
    
    for (auto& entity : Entity::GetEntities()) {
        camera_cmp = entity->GetComponent<CameraComponent>();


        if (camera_cmp != nullptr) {
            camera_entity = entity.get();
            break;
        }
    }

    if (camera_cmp == nullptr) {
        err::LogError("No Camera Found! Cannot draw entities!");
        return;
    }
    
    TransformComponent* camera_trans = camera_entity->GetComponent<TransformComponent>();

    DirectX::XMVECTOR camera_direction = DirectX::XMLoadFloat3(&camera_cmp->mDirection);
    DirectX::XMVECTOR camera_pos = DirectX::XMLoadFloat3(&camera_trans->mTranslation);
    DirectX::XMVECTOR up_vector = DirectX::XMLoadFloat3(&Constants::UP_VECTOR);

    D3DBuffer::mEntityTransform.mView = DirectX::XMMatrixLookToRH(camera_pos, camera_direction, up_vector);

    // Loop through entities to draw them
    for (auto& entity : Entity::GetEntities()) {
        TransformComponent *trans = entity->GetComponent<TransformComponent>();
        GraphicsComponent *graphics = entity->GetComponent<GraphicsComponent>();

            // Requires Transform and Graphics components to be drawn
        if (!trans || !graphics)
            continue;

        graphics->mShaderProgram->Bind();

        D3DBuffer::mEntityTransform.mModel = 
            DirectX::XMMatrixTranslation(trans->mTranslation.x, 
                                         trans->mTranslation.y, 
                                         trans->mTranslation.z);

        std::pair<UINT, UINT> resolution = Window::GetInstance()->GetResolution();

        D3DBuffer::mEntityTransform.mProjection =
            DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(80.0f), 
                                              static_cast<float>(resolution.first) / 
                                              static_cast<float>(resolution.second),
                                              0.1f, 100.0f);

       

        if (graphics->mShaderProgram)
            graphics->mShaderProgram->Bind();
        else
            err::LogError("Graphics Component does not contain a shader program to bind.");
        
        if (graphics->mModel)
            graphics->mModel->Draw();
        else
            err::LogError("Graphics Component does not contain a model program to draw.");
    }
}

} // namespace TwilliEngine