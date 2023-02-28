#pragma once
#include "Systems/WorldSystem/Scenes/Scene.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"
#include "Resources/StructuredBuffer/StructuredBuffer.hpp"
#include "Resources/Material/Material.hpp"

#include "Resources/D3DBuffer/ConstantBufferDefinitions.hpp"
#include "Resources/StructuredBuffer/StructuredBufferDefinitions.hpp"

#include "DirectXTK/Keyboard.h"
#include "DirectXTK/Mouse.h"

namespace TwilliEngine
{

struct Transform
{
    DirectX::XMFLOAT3 mTranslation;
    DirectX::XMFLOAT3 mRotation;
    DirectX::XMFLOAT3 mScale;
};

struct SphericalPolarCoordinates
{
    SphericalPolarCoordinates() : mPhi(),
                                  mTheta(),
                                  mRadius(), 
                                  mPhiRadiansPerFrame(), 
                                  mThetaRadiansPerFrame() {}

    void UpdateFrame() {
        mPhi += mPhiRadiansPerFrame;
        mTheta += mThetaRadiansPerFrame;
    }

    float mPhi;
    float mTheta;
    
    float mRadius;

    float mPhiRadiansPerFrame;
    float mThetaRadiansPerFrame;
};

class DefaultScene : public Scene
{
public:
    DefaultScene();
    ~DefaultScene();

    void StartFrame() override;
    void Update(float dt) override;
    void EndFrame() override;

private:
    void UpdateImGui();
    void UpdateCamera();
    
    void UpdateLights();

    void Draw();
    void LoadTransformBuffer(const Transform& transform);
    DirectX::Mouse::ButtonStateTracker mMouseTracker;

    bool mDisplayNormals;

    // Shaders
    //////////////////////////
    ShaderProgram::Key mPhongShader;
    ShaderProgram::Key mNormalDisplayShader;
    ShaderProgram::Key mLightDisplayShader;

    // Models
    //////////////////////////
    Model::Key mSphereModel;

    Model::Key mCurrentModel;
    std::vector<Model::Key> mModels;

    // Camera Data
    //////////////////////////
    DirectX::XMFLOAT3 mCameraPosition;
    DirectX::XMFLOAT3 mCameraView;
    DirectX::XMFLOAT2 mCameraAngles;

    float mCameraRotationScale;
    float mCameraMovementScale;

    // Main Object
    //////////////////////////
    Transform mMainObjectTransform;    
    Material::Key mMainObjectMaterial;

    // Lights
    //////////////////////////
    static const size_t NUM_LIGHTS = 6;

    SphericalPolarCoordinates mLightPositions[NUM_LIGHTS];
    Material::Key mLightMaterial[NUM_LIGHTS];
    

    // Platform
    //////////////////////////
    Transform mPlatformTransform;
    Material::Key mPlatformMaterial;
    Model::Key mCubeModel;
 
    // Buffers
    //////////////////////////

        // Entity
    EntityTransform mEntityTransformData;
    D3DBuffer::Key mEntityTransformBuffer;

    D3DBuffer::Key mEntityMaterialBuffer;
    
        // Lights
    Light mLights[NUM_LIGHTS];
    StructuredBuffer::Key mLightsBuffer;

        // View Vector
    ViewVector mViewVector;
    D3DBuffer::Key mViewVectorBuffer;

        // Color
    Color mColor;
    D3DBuffer::Key mColorBuffer;
};

} // namespace TwilliEngine