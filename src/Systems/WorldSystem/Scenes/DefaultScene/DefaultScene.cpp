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
    mEntityMaterialBuffer = D3DBuffer::GetResourceWithName("Material");
    mLightsBuffer = StructuredBuffer::GetResourceWithName("Light");
    mViewVectorBuffer = D3DBuffer::GetResourceWithName("ViewVector");

    mCameraPosition = { 0.0f, 0.0f, 1.0f };
    mCameraView = { 0.0f, 0.0f, -1.0f };

    mBunnyTransform.mTranslation = { 0.0f, 0.0f, 0.0f };
    mBunnyTransform.mRotation = { 0.0f, 0.0f, 0.0f };
    mBunnyTransform.mScale = {4.0f, 4.0f, 4.0f};

    mBunnyMaterial = Material::Create("BunnyMaterial");

    mBunnyMaterial->mAmbientColor = { 0.1f, 0.1f, 0.1f, 1.0f };
    mBunnyMaterial->mEmissiveColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    mBunnyMaterial->mDiffuseColor = { 0.1f, 0.1f, 0.1f, 1.0f };
    mBunnyMaterial->mSpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    mBunnyMaterial->mSpecularPower = 1.0f;

    mLights[0].mEnabled = true;
    mLights[0].mPositionWorldSpace = { 2.0f, 2.0f, 2.0f };
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

        ImGui::Text("Transform");
        ImGui::DragFloat3("Translation", &mBunnyTransform.mTranslation.x, 0.1f);
        ImGui::DragFloat3("Rotation", &mBunnyTransform.mRotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &mBunnyTransform.mScale.x, 0.1f, 0.0f);

        ImGui::Text("Material");
        ImGui::DragFloat4("Ambient Color", &mBunnyMaterial->mAmbientColor.x, 0.1f);
        ImGui::DragFloat4("Emissive Color", &mBunnyMaterial->mEmissiveColor.x, 0.1f);
        ImGui::DragFloat4("Diffuse Color", &mBunnyMaterial->mDiffuseColor.x, 0.1f);
        ImGui::DragFloat4("Specular Color", &mBunnyMaterial->mSpecularColor.x, 0.1f);

        ImGui::DragFloat("Specular Power", &mBunnyMaterial->mSpecularPower, 0.1f);
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
    
    mViewVector.mCameraPosition = mCameraPosition;

    mEntityTransformBuffer->MapData(static_cast<void*>(&mEntityTransformData));
    mLightsBuffer->MapData(static_cast<void*>(&mLights));
    mEntityMaterialBuffer->MapData(static_cast<void*>(&mBunnyMaterial->mAmbientColor));
    mViewVectorBuffer->MapData(static_cast<void*>(&mViewVector));

    mBunnyShader->Bind();
    mBunnyModel->Draw();
}

void DefaultScene::EndFrame()
{
}

} // namespace TwilliEngine