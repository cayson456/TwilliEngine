#include "precompiled.hpp"
#include "D3DBuffer.hpp"

namespace TwilliEngine
{
D3DBuffer::D3DBuffer(ID3D11Device* device, 
                     const std::string& name, UINT byte_width) : mIsBuilt(false),
                                                                 mByteWidth(byte_width), 
                                                                 mBuffer(nullptr)
{
    D3D11_BUFFER_DESC desc;
    {
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.ByteWidth = byte_width;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.Usage = D3D11_USAGE_DYNAMIC;

        HRESULT hr = device->CreateBuffer(&desc, nullptr, &mBuffer);

        if (err::HRCheck(hr))
            mIsBuilt = true;
    }
}

D3DBuffer::~D3DBuffer()
{
}

void D3DBuffer::MapData(ID3D11DeviceContext* context, void* data)
{
    D3D11_MAPPED_SUBRESOURCE mapped_buffer;
    HRESULT hr = context->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

    if (!err::HRCheck(hr))
        return;

    std::memcpy(mapped_buffer.pData, data, mByteWidth);
    context->Unmap(mBuffer, 0);
}
} // namespace TwilliEngine