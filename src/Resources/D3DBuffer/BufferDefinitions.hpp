#pragma once

namespace TwilliEngine
{

struct Buffer
{
    Buffer() {}
    virtual ~Buffer() = 0;
};

struct EntityTransform : public Buffer
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
}