#pragma once
#include "Resources/ResourceBase.hpp"

namespace TwilliEngine
{
class Material : public ResourceBase<Material>
{
public:
    Material() : mAmbientColor({0.0f, 0.0f, 0.0f, 1.0f}),
                 mEmissiveColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                 mDiffuseColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                 mSpecularColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                 mReflectance({ 0.0f, 0.0f, 0.0f, 1.0f }),
                 mOpacity(1.0f),
                 mSpecularPower(1.0f),
                 mIndexOfRefraction(1.0f),
                 mHasAmbientTexture(false),
                 mHasSpecularTexture(false),
                 mHasNormalTexture(false),
                 mHasBumpTexture(false),
                 mBumpIntensity(1.0f),
                 mSpecularScale(1.0f),
                 mAlphaThreshold(1.0f) {}

    Material(std::string_view name) : ResourceBase(name),
                                      mAmbientColor({0.0f, 0.0f, 0.0f, 1.0f}),
                                      mEmissiveColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                                      mDiffuseColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                                      mSpecularColor({ 0.0f, 0.0f, 0.0f, 1.0f }),
                                      mReflectance({ 0.0f, 0.0f, 0.0f, 1.0f }),
                                      mOpacity(1.0f),
                                      mSpecularPower(1.0f),
                                      mIndexOfRefraction(1.0f),
                                      mHasAmbientTexture(false),
                                      mHasSpecularTexture(false),
                                      mHasNormalTexture(false),
                                      mHasBumpTexture(false),
                                      mBumpIntensity(1.0f),
                                      mSpecularScale(1.0f),
                                      mAlphaThreshold(1.0f) {}

private:

    DirectX::XMFLOAT4 mAmbientColor;
    DirectX::XMFLOAT4 mEmissiveColor;
    DirectX::XMFLOAT4 mDiffuseColor;
    DirectX::XMFLOAT4 mSpecularColor;
    DirectX::XMFLOAT4 mReflectance;
    
    float mOpacity;
    float mSpecularPower;
    float mIndexOfRefraction;
    
    bool mHasAmbientTexture;
    bool mHasEmissiveTexture;
    bool mHasSpecularTexture;
    bool mHasNormalTexture;
    bool mHasBumpTexture;

    float mBumpIntensity;
    float mSpecularScale;
    float mAlphaThreshold;
};
} // namespace TwilliEngine