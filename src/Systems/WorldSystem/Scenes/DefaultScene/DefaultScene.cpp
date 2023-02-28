#include "precompiled.hpp"
#include "DefaultScene.hpp"

#include "Singletons/Window/Window.hpp"
#include "imgui/imgui.h"


using namespace DirectX;

namespace TwilliEngine
{

DefaultScene::DefaultScene()
{
    mDisplayNormals = false;

    // Shaders
    //////////////////////////
    mPhongShader = ShaderProgram::GetResourceWithName("PhongShader");
    
    mLightDisplayShader = ShaderProgram::GetResourceWithName("LightDisplayShader");
    mNormalDisplayShader = ShaderProgram::GetResourceWithName("NormalDisplayShader");
    
    // Models
    //////////////////////////
    mSphereModel = Model::GetResourceWithName("globe-sphere");
    mCubeModel = Model::GetResourceWithName("cube");

    mCurrentModel = Model::GetResourceWithName("bunny");
    
    mModels.push_back(Model::GetResourceWithName("bunny"));
    mModels.push_back(Model::GetResourceWithName("globe-sphere"));
    mModels.push_back(Model::GetResourceWithName("bakedpotato"));
    mModels.push_back(Model::GetResourceWithName("cube"));
    
    // Camera Data
    //////////////////////////
    mCameraPosition = { -10.0f, 3.0f, 0.0f };
    mCameraView = { 0.0f, 0.0f, -1.0f };
    mCameraAngles = { 0.0f, -0.3f };

    mCameraRotationScale = 0.1f;
    mCameraMovementScale = 0.05f;

    // Main Object
    //////////////////////////
    mMainObjectTransform.mTranslation = { 0.0f, 0.0f, 0.0f };
    mMainObjectTransform.mRotation = { 0.0f, 0.0f, 0.0f };
    mMainObjectTransform.mScale = {4.0f, 4.0f, 4.0f};

    mMainObjectMaterial = Material::Create("Main Object Material");

    mMainObjectMaterial->mAmbientColor = { 0.05f, 0.05f, 0.05f, 1.0f };
    mMainObjectMaterial->mEmissiveColor = { 0.0f, 0.0f, 0.0f, 1.0f };
    mMainObjectMaterial->mDiffuseColor = { 0.3f, 0.3f, 0.3f, 1.0f };
    mMainObjectMaterial->mSpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    mMainObjectMaterial->mSpecularPower = 16.0f;

    // Lights
    //////////////////////////

        // Light 0
    {
        mLights[0].mEnabled = true;
        mLightPositions[0].mPhi = 0.0f;
        mLightPositions[0].mTheta = 0.0f;
        mLightPositions[0].mPhiRadiansPerFrame = (Constants::PI / 128.0f);
        mLightPositions[0].mThetaRadiansPerFrame = 0.0f;
        mLightPositions[0].mRadius = 4.0f;

        XMFLOAT4 Light_Color_0 = { 1.0f, 1.0f, 1.0f, 1.0f };
        mLightMaterial[0] = Material::Create("Light Material 0");
        mLightMaterial[0]->mAmbientColor = Light_Color_0;
        mLights[0].mColor = Light_Color_0;
    }

        // Light 1
    {
        mLights[1].mEnabled = true;
        mLightPositions[1].mPhi = Constants::PI;
        mLightPositions[1].mTheta = Constants::PI;
        mLightPositions[1].mPhiRadiansPerFrame = (Constants::PI / 128.0f);
        mLightPositions[1].mThetaRadiansPerFrame = (Constants::PI / 128.0f);
        mLightPositions[1].mRadius = 7.0f;

        XMFLOAT4 Light_Color_1 = { 0.8f, 0.0f, 0.0f, 1.0f };
        mLightMaterial[1] = Material::Create("Light Material 1");
        mLightMaterial[1]->mAmbientColor = Light_Color_1;
        mLights[1].mColor = Light_Color_1;
    }

        // Light 2
    {
        mLights[2].mEnabled = true;
        mLightPositions[2].mPhi = 0.0f;
        mLightPositions[2].mTheta = 0.0f;
        mLightPositions[2].mPhiRadiansPerFrame = (Constants::PI / 128.0f);
        mLightPositions[2].mThetaRadiansPerFrame = (Constants::PI / 128.0f);
        mLightPositions[2].mRadius = 6.0f;

        XMFLOAT4 Light_Color_2 = { 0.0f, 0.8f, 0.0f, 1.0f };
        mLightMaterial[2] = Material::Create("Light Material 2");
        mLightMaterial[2]->mAmbientColor = Light_Color_2;
        mLights[2].mColor = Light_Color_2;
    }

        // Light 3
    {
        mLights[3].mEnabled = true;
        mLightPositions[3].mPhi = 0.0f;
        mLightPositions[3].mTheta = 0.0f;
        mLightPositions[3].mPhiRadiansPerFrame = 0.0f;
        mLightPositions[3].mThetaRadiansPerFrame = (Constants::PI / 256.0f);
        mLightPositions[3].mRadius = 6.0f;

        XMFLOAT4 Light_Color_3 = { 0.0f, 0.0f, 0.8f, 1.0f };
        mLightMaterial[3] = Material::Create("Light Material 3");
        mLightMaterial[3]->mAmbientColor = Light_Color_3;
        mLights[3].mColor = Light_Color_3;
    }

    // Platform
    //////////////////////////
    mPlatformTransform.mScale = { 20.0f, 0.5f, 20.0f };
    mPlatformTransform.mRotation = { 0.0f, 0.0f, 0.0f };
    mPlatformTransform.mTranslation = { 0.0f, -3.0f, 0.0f };

    mPlatformMaterial = Material::Create("Platform Material");
    mPlatformMaterial->mAmbientColor = { 0.1f, 0.1f, 0.1f, 1.0f };
    mPlatformMaterial->mDiffuseColor = { 0.4f, 0.4f, 0.4f , 1.0f };
    mPlatformMaterial->mSpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    mPlatformMaterial->mSpecularPower = 16.0f;

    // Find Buffers
    //////////////////////////
    mEntityTransformBuffer = D3DBuffer::GetResourceWithName("EntityTransform");
    mEntityMaterialBuffer = D3DBuffer::GetResourceWithName("Material");
    
    mColorBuffer = D3DBuffer::GetResourceWithName("Color");
    mViewVectorBuffer = D3DBuffer::GetResourceWithName("ViewVector");

    mLightsBuffer = StructuredBuffer::GetResourceWithName("Light");
   
    // Normal Display
    //////////////////////////
    mColor.mColor = { 0.7f, 0.7f, 0.7f, 1.0f };
    mColorBuffer->MapData(static_cast<void*>(&mColor));
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::StartFrame()
{
}

void DefaultScene::Update(float)
{
    UpdateCamera();
    UpdateLights();
    UpdateImGui();

    Draw();
}

void DefaultScene::EndFrame()
{
}

void DefaultScene::UpdateImGui()
{
    ImGui::Begin("Data");

        // Camera Info
        //////////////////////////
    {
        ImGui::BeginGroup();
        ImGui::Text("Camera");

        ImGui::InputFloat3("Camera Position", &mCameraPosition.x);
        ImGui::InputFloat2("Camera Rotation", &mCameraAngles.x);
        ImGui::InputFloat3("Normalized View Vector", &mCameraView.x);

        ImGui::EndGroup();
    }

        // Main Object Info
        //////////////////////////
    {
        ImGui::BeginGroup();
        ImGui::Text("Main Object");
        ImGui::Separator();

        ImGui::Text("Loaded Model");
        for (auto model : mModels) {
            if(ImGui::Selectable(model->mName.c_str()))
                mCurrentModel = model;
        }
        ImGui::Spacing();

        ImGui::Checkbox("Display Normals", &mDisplayNormals);
        ImGui::Spacing();

        ImGui::Text("Transform");
        ImGui::DragFloat3("Translation", &mMainObjectTransform.mTranslation.x, 0.1f);
        ImGui::DragFloat3("Rotation", &mMainObjectTransform.mRotation.x, 0.1f);
        ImGui::DragFloat3("Scale", &mMainObjectTransform.mScale.x, 0.1f, 0.0f);
        ImGui::Spacing();

        ImGui::Text("Material");
        ImGui::DragFloat4("Ambient Color", &mMainObjectMaterial->mAmbientColor.x, 0.1f);
        ImGui::DragFloat4("Emissive Color", &mMainObjectMaterial->mEmissiveColor.x, 0.1f);
        ImGui::DragFloat4("Diffuse Color", &mMainObjectMaterial->mDiffuseColor.x, 0.1f);
        ImGui::DragFloat4("Specular Color", &mMainObjectMaterial->mSpecularColor.x, 0.1f);
        ImGui::DragFloat("Specular Power", &mMainObjectMaterial->mSpecularPower, 0.1f);
        ImGui::Spacing();

        ImGui::EndGroup();
    }

    {
        ImGui::BeginGroup();
        ImGui::Text("Lights");
        ImGui::Separator();

        for (size_t i = 0; i < NUM_LIGHTS; ++i) {
            std::string light_name = "Light " + std::to_string(i);
            ImGui::Text(light_name.c_str());
            ImGui::InputFloat3("Position", &(mLights[i].mPositionWorldSpace.x));
            ImGui::ColorEdit3("Color", &(mLights[i].mColor.x));
            ImGui::Spacing();
        }

        ImGui::EndGroup();
    }

    ImGui::End();
}

void DefaultScene::UpdateCamera()
{
    // Input for camera movement
    //////////////////////////
    Mouse::State mouse_state = Mouse::Get().GetState();

    if (mMouseTracker.leftButton == Mouse::ButtonStateTracker::HELD &&
        mouse_state.positionMode == Mouse::MODE_RELATIVE)
    {
        float dx = mouse_state.x * mCameraRotationScale;
        float dy = mouse_state.y * mCameraRotationScale;

        mCameraAngles.x = mCameraAngles.x + (dx * mCameraRotationScale);
        mCameraAngles.y = std::clamp(mCameraAngles.y - (dy * mCameraRotationScale), Constants::PI / 2.1f * -1.0f + Constants::EPSILON, Constants::PI / 2.1f);
    }

    mCameraView.x = std::cosf(mCameraAngles.x) * std::cosf(mCameraAngles.y);
    mCameraView.y = std::sinf(mCameraAngles.y);
    mCameraView.z = std::sinf(mCameraAngles.x) * std::cosf(mCameraAngles.y);

    if (mMouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
        Mouse::Get().SetMode(Mouse::MODE_RELATIVE);
    if (mMouseTracker.leftButton == Mouse::ButtonStateTracker::RELEASED)
        Mouse::Get().SetMode(Mouse::MODE_ABSOLUTE);

    mMouseTracker.Update(mouse_state);

    Keyboard::State keyboard_state = Keyboard::Get().GetState();

    XMVECTOR camera_pos = XMLoadFloat3(&mCameraPosition);
    XMVECTOR camera_forward = XMLoadFloat3(&mCameraView);
    XMVECTOR camera_right = XMVector3Normalize(XMVector3Cross(camera_forward, XMLoadFloat3(&Constants::UP_VECTOR)));

    if (keyboard_state.IsKeyDown(Keyboard::Keys::W))
        camera_pos += camera_forward * mCameraMovementScale;
    if (keyboard_state.IsKeyDown(Keyboard::Keys::A))
        camera_pos -= camera_right * mCameraMovementScale;
    if (keyboard_state.IsKeyDown(Keyboard::Keys::S))
        camera_pos -= camera_forward * mCameraMovementScale;
    if (keyboard_state.IsKeyDown(Keyboard::Keys::D))
        camera_pos += camera_right * mCameraMovementScale;

    XMStoreFloat3(&mCameraPosition, camera_pos);

}

void DefaultScene::UpdateLights()
{
    for (size_t i = 0; i < NUM_LIGHTS; ++i) {
        mLightPositions[i].UpdateFrame();
        
        mLights[i].mPositionWorldSpace.x = mLightPositions[i].mRadius * std::cosf(mLightPositions[i].mPhi) * std::cosf(mLightPositions[i].mTheta);
        mLights[i].mPositionWorldSpace.y = mLightPositions[i].mRadius * std::sinf(mLightPositions[i].mTheta);
        mLights[i].mPositionWorldSpace.z = mLightPositions[i].mRadius * std::sinf(mLightPositions[i].mPhi) * std::cosf(mLightPositions[i].mTheta);

        mLightsBuffer->MapData(static_cast<void*>(mLights));
    }
}

void DefaultScene::Draw()
{
    mLightsBuffer->MapData(static_cast<void*>(&mLights));

    mViewVector.mCameraPosition = mCameraPosition;
    mViewVectorBuffer->MapData(static_cast<void*>(&mViewVector));

        // Main Object
    LoadTransformBuffer(mMainObjectTransform);
    mEntityMaterialBuffer->MapData(static_cast<void*>(&mMainObjectMaterial->mAmbientColor));
    
    mPhongShader->Bind();
    D3D::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    mCurrentModel->Draw();

    if (mDisplayNormals) {
        mNormalDisplayShader->Bind();
        D3D::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
        mCurrentModel->Draw();
    }

        // Platform
    LoadTransformBuffer(mPlatformTransform);
    mEntityMaterialBuffer->MapData(static_cast<void*>(&mPlatformMaterial->mAmbientColor));
   
    mPhongShader->Bind();
    D3D::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    mCubeModel->Draw();


    // Render Lights
    mLightDisplayShader->Bind();
    D3D::GetInstance()->GetContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    for (size_t i = 0; i < NUM_LIGHTS; ++i) {
        if (mLights[i].mEnabled) {
            mLightMaterial[i]->mAmbientColor = mLights[i].mColor;

            DirectX::XMMATRIX light_translation = XMMatrixTranslation(mLights[i].mPositionWorldSpace.x,
                                                                     mLights[i].mPositionWorldSpace.y,
                                                                     mLights[i].mPositionWorldSpace.z);

            mEntityTransformData.mModel = DirectX::XMMatrixTranspose(light_translation);

            
            mEntityTransformBuffer->MapData(static_cast<void*>(&mEntityTransformData));
            mEntityMaterialBuffer->MapData(static_cast<void*>(&(mLightMaterial[i]->mAmbientColor)));
            mSphereModel->Draw();
        }
    }
}

void DefaultScene::LoadTransformBuffer(const Transform& transform)
{
    // Transpose to turn into row-major matrices for hlsl
    // DirectX Math uses column-major matrices
    // We use row-vector multiplication no matter what, and doesnt matter whether it's row-major matrices
    // or column major matrices. (this means we multiply left to right, regardless of the matrices
    // http://www.catalinzima.com/2012/12/a-word-on-matrices/
    // hlsl corrects the matrices based on whether or not we multiply left to right or right to left,
    // as far as i understand

    DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(transform.mTranslation.x,
                                                                 transform.mTranslation.y,
                                                                 transform.mTranslation.z);

    DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(transform.mRotation.x,
                                                                       transform.mRotation.y,
                                                                       transform.mRotation.z);

    DirectX::XMMATRIX scale = DirectX::XMMatrixScaling(transform.mScale.x,
                                                       transform.mScale.y,
                                                       transform.mScale.z);

    mEntityTransformData.mModel = DirectX::XMMatrixTranspose(scale * rotation * translation);

    mEntityTransformData.mView = 
        DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtRH(DirectX::XMLoadFloat3(&mCameraPosition),
                                                             DirectX::XMLoadFloat3(&mCameraView) + DirectX::XMLoadFloat3(&mCameraPosition),
                                                             DirectX::XMLoadFloat3(&Constants::UP_VECTOR)));

    mEntityTransformData.mTransInvModel = DirectX::XMMatrixTranspose(rotation);

    std::pair<UINT, UINT> resolution = Window::GetInstance()->GetResolution();

    mEntityTransformData.mProjection =
        DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovRH(DirectX::XMConvertToRadians(80.0f),
                                                                     static_cast<float>(resolution.first) /
                                                                     static_cast<float>(resolution.second),
                                                                     0.1f, 100.0f));

    mEntityTransformBuffer->MapData(static_cast<void*>(&mEntityTransformData));
}



} // namespace TwilliEngine