#include "precompiled.hpp"
#include "D3D.hpp"

namespace TwilliEngine 
{

D3D::D3D() : mDevice(nullptr), mDeviceContext(nullptr), 
             mFeatureLevel(D3D_FEATURE_LEVEL_1_0_CORE),
             mDriverType(D3D_DRIVER_TYPE_NULL)
{
    // Specify Drivers and Features
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_REFERENCE
    };

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };

    unsigned total_driver_types = ARRAYSIZE(driver_types);
    unsigned total_feature_levels = ARRAYSIZE(feature_levels);

    unsigned creation_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
    creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // Try each driver type
    for (unsigned i = 0; i < total_driver_types; ++i) {
        HRESULT hr = D3D11CreateDevice(0, driver_types[i], 0, creation_flags,
            feature_levels, total_feature_levels, D3D11_SDK_VERSION,
            &mDevice, &mFeatureLevel, &mDeviceContext);

        if (SUCCEEDED(hr)) {
            mDriverType = driver_types[i];
            break;
        }
    }
}

D3D::~D3D()
{
    SafeRelease(mDeviceContext);
    SafeRelease(mDevice);
}



} // namespace TwilliEngine