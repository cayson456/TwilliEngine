#pragma once
#include "Resources/ResourceBase.hpp"

namespace TwilliEngine
{
class D3DBuffer : public ResourceBase<D3DBuffer>
{
public:
    D3DBuffer(ID3D11Device *device, const std::string &name, UINT byte_width);
    ~D3DBuffer();

    void MapData(ID3D11DeviceContext* context, void* data);

private:
    bool mIsBuilt;

    UINT mByteWidth;
    ID3D11Buffer* mBuffer;
};

} // namespace TwilliEngine