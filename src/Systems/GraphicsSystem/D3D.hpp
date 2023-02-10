#pragma once

namespace TwilliEngine
{
class D3D
{
public:
    D3D();
    ~D3D();

    ID3D11Device* GetDevice() { return mDevice; }
    ID3D11DeviceContext* GetContext() { return mDeviceContext; }

private:

    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;

    D3D_FEATURE_LEVEL mFeatureLevel;
    D3D_DRIVER_TYPE mDriverType;
};

} // namespace TwilliEngine