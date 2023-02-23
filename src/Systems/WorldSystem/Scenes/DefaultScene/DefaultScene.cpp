#include "precompiled.hpp"
#include "DefaultScene.hpp"

#include "Singletons/Window/Window.hpp"
#include "imgui/imgui.h"

namespace TwilliEngine
{

DefaultScene::DefaultScene()
{
    // Bunny Entity
    mBunnyShader = ShaderProgram::GetResourceWithName("PhongShader");
    mBunnyModel = Model::GetResourceWithName("bunny");
    mEntityTransformBuffer = D3DBuffer::GetResourceWithName("EntityTransform");

    mCameraPosition = { 0.0f, 0.0f, 1.0f };
    mCameraView = { 0.0f, 0.0f, -1.0f };

    mBunnyTransform.mTranslation = { 0.0f, 0.0f, 0.0f };
    mBunnyTransform.mRotation = { 0.0f, 0.0f, 0.0f };
    mBunnyTransform.mScale = {4.0f, 4.0f, 4.0f};
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::StartFrame()
{
}

void DefaultScene::Update(float)
{
    {
        ImGui::Begin("Bunny");

        ImGui::DragFloat3("Translation", &mBunnyTransform.mTranslation.x, 0.1f);
        ImGui::DragFloat3("Rotation", &mBunnyTransform.mRotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &mBunnyTransform.mScale.x, 0.1f, 0.0f);

        ImGui::End();
    }


        // Transpose to turn into row-major for hlsl
        // DirectX Math uses column-major

    DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(mBunnyTransform.mTranslation.x,
                                                                 mBunnyTransform.mTranslation.y,
                                                                 mBunnyTransform.mTranslation.z);

    DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(mBunnyTransform.mRotation.x,
                                                                       mBunnyTransform.mRotation.y,
                                                                       mBunnyTransform.mRotation.z);

    DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(mBunnyTransform.mScale.x,
                                                       mBunnyTransform.mScale.y,
                                                       mBunnyTransform.mScale.z);


    mEntityTransformData.mModel =
        DirectX::XMMatrixTranspose(scale * rotation * translation);

    mEntityTransformData.mView =
       DirectX::XMMatrixTranspose(DirectX::XMMatrixLookToRH(DirectX::XMLoadFloat3(&mCameraPosition), 
                                                            DirectX::XMLoadFloat3(&mCameraView), 
                                                            DirectX::XMLoadFloat3(&Constants::UP_VECTOR)));
    
    std::pair<UINT, UINT> resolution = Window::GetInstance()->GetResolution();

    mEntityTransformData.mProjection =
        DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(80.0f),
                                                                     static_cast<float>(resolution.first) /
                                                                     static_cast<float>(resolution.second),
                                                                     0.1f, 100.0f));
    
    mEntityTransformBuffer->MapData(static_cast<void*>(&mEntityTransformData));

    mBunnyShader->Bind();
    mBunnyModel->Draw();
}

void DefaultScene::EndFrame()
{
}

} // namespace TwilliEngine