#pragma once
#include "Systems/WorldSystem/Scenes/Scene.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"
#include "Resources/StructuredBuffer/StructuredBuffer.hpp"
#include "Resources/Material/Material.hpp"

#include "Resources/D3DBuffer/ConstantBufferDefinitions.hpp"
#include "Resources/StructuredBuffer/StructuredBufferDefinitions.hpp"

namespace TwilliEngine
{

struct Transform
{
    DirectX::XMFLOAT3 mTranslation;
    DirectX::XMFLOAT3 mRotation;
    DirectX::XMFLOAT3 mScale;
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
    Model::Key mBunnyModel;
    ShaderProgram::Key mBunnyShader;

    DirectX::XMFLOAT3 mCameraPosition;
    DirectX::XMFLOAT3 mCameraView;

    ViewVector mViewVector;

    Transform mBunnyTransform;
    Material::Key mBunnyMaterial;

    EntityTransform mEntityTransformData;
    D3DBuffer::Key mEntityTransformBuffer;
    D3DBuffer::Key mEntityMaterialBuffer;
    D3DBuffer::Key mViewVectorBuffer;

    Light mLights[6];
    StructuredBuffer::Key mLightsBuffer;
};

} // namespace TwilliEngine