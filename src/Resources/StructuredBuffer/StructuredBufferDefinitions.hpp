#pragma once

// must match the define in hlsl file
#define NUM_LIGHTS_MAX 6

namespace TwilliEngine
{


// for structued buffer 
struct Light
{
    Light() : mPositionWorldSpace({0.0f, 0.0f, 0.0f}),
              mDirectionWorldSpace({ 0.0f, 0.0f, 0.0f }),
              mPositionViewSpace({ 0.0f, 0.0f, 0.0f }),
              mDirectionViewSpace({ 0.0f, 0.0f, 0.0f }),
              mColor({ 0.0f, 0.0f, 0.0f, 1.0f}),
              mSpotLightAngle(80.0f),
              mRange(5.0f),
              mEnabled(false),
              mType(0),
              __padding() {}

    ~Light() {}

    DirectX::XMFLOAT3 mPositionWorldSpace;
    DirectX::XMFLOAT3 mDirectionWorldSpace;
    DirectX::XMFLOAT3 mPositionViewSpace;
    DirectX::XMFLOAT3 mDirectionViewSpace;

    DirectX::XMFLOAT4 mColor;
    float mSpotLightAngle;
    float mRange;

    bool mEnabled;
    int mType;

    int __padding[3];
};


} // namespace TwilliEngine