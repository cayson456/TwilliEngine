#pragma once

namespace TwilliEngine
{

// for cbuffer EntityTransform
struct EntityTransform
{
    EntityTransform() : mModel(DirectX::XMMatrixIdentity()),
                        mView(DirectX::XMMatrixIdentity()),
                        mProjection(DirectX::XMMatrixIdentity()),
                        mTransInvModel(DirectX::XMMatrixIdentity()) {}

    DirectX::XMMATRIX mModel;
    DirectX::XMMATRIX mView;
    DirectX::XMMATRIX mProjection;
    DirectX::XMMATRIX mTransInvModel;
};

// for cbuffer ViewVector
struct ViewVector
{
    DirectX::XMFLOAT3 mCameraPosition;
    int32_t __padding;
};

}