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
              mColor({ 1.0f, 1.0f, 1.0f, 1.0f}),
              mSpotLightAngle(80.0f),
              mRange(5.0f),
              mEnabled(false),
              __bool_padding(),
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

        // Boots are 4 bytes in hlsl, so we needa pad it with 3 extra ones
    bool mEnabled;
    bool __bool_padding[3];

    uint32_t mType;

    uint32_t __padding[3];
};


} // namespace TwilliEngine