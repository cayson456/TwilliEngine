#pragma once
#include "Components/Component.hpp"

#include "Resources/Model/Model.hpp"
#include "Resources/Shader/ShaderProgram.hpp"

namespace TwilliEngine
{
class CameraComponent : public Component
{
public:
    CameraComponent() : mDirection() {}
    CameraComponent(std::string_view name) : Component(name), mDirection() {}
    ~CameraComponent() {}

    DirectX::XMFLOAT3 mDirection;
};

} // namespace TwilliEngine