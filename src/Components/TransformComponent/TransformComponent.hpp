#pragma once
#include "Components/Component.hpp"

namespace TwilliEngine
{
class TransformComponent : public Component
{
public:
    TransformComponent() {}
    TransformComponent(const std::string& name) : Component(name) {}
    ~TransformComponent() {}

    DirectX::XMFLOAT3 mTranslation;
    DirectX::XMFLOAT3 mRotation;
    DirectX::XMFLOAT3 mScale;

};
} // namespace TwilliEngine