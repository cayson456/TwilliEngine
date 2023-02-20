#include "precompiled.hpp"
#include "DefaultScene.hpp"

#include "Components/Entity/Entity.hpp"
#include "Components/GraphicsComponent/GraphicsComponent.hpp"
#include "Components/TransformComponent/TransformComponent.hpp"
#include "Components/CameraComponent/CameraComponent.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"

namespace TwilliEngine
{

DefaultScene::DefaultScene()
{
    mBunny = Entity::CreateEntity("Bunny");
    {
        mBunny->AddComponent<TransformComponent>();

        GraphicsComponent* bunny_graphics = mBunny->AddComponent<GraphicsComponent>();
        bunny_graphics->mShaderProgram = ShaderProgram::GetResourceWithName("PhongShader");
        bunny_graphics->mModel = Model::GetResourceWithName("bunny");
    }

    mCamera = Entity::CreateEntity("Camera");
    {
        TransformComponent* camera_transform = mCamera->AddComponent<TransformComponent>();
        CameraComponent* camera_camera = mCamera->AddComponent<CameraComponent>();

        camera_transform->mTranslation = { 0.0f, 0.0f, 1.0f };
        camera_camera->mDirection = { 0.0f, 0.0f, -1.0f };
    }
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::StartFrame()
{
}

void DefaultScene::Update(float)
{
}

void DefaultScene::EndFrame()
{
}

} // namespace TwilliEngine