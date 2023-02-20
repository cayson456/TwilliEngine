#pragma once
#include "Components/Component.hpp"

namespace TwilliEngine
{
class TransformComponent : public Component
{
public:
    TransformComponent() : mTranslation({0.0f, 0.0f, 0.0f}), 
                           mRotation({0.0f, 0.0f, 0.0f}), 
                           mScale({1.0f, 1.0f, 1.0f}) {}

    TransformComponent(const std::string_view name) : Component(name), 
                                                      mTranslation({ 0.0f, 0.0f, 0.0f }), 
                                                      mRotation({ 0.0f, 0.0f, 0.0f }), 
                                                      mScale({ 1.0f, 1.0f, 1.0f }) {}

    ~TransformComponent() {}

    DirectX::XMFLOAT3 mTranslation;
    DirectX::XMFLOAT3 mRotation;
    DirectX::XMFLOAT3 mScale;

};
} // namespace TwilliEngine