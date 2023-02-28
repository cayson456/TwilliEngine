#include "precompiled.hpp"
#include "D3DBuffer.hpp"

namespace TwilliEngine
{
bool D3DBuffer::Build(UINT byte_width)
{
    if (mIsBuilt) {
        err::LogError("Attempted to build already built buffer ", mName);
        return false;
    }

    D3D11_BUFFER_DESC desc;
    {
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.ByteWidth = byte_width;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.Usage = D3D11_USAGE_DYNAMIC;

        HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, nullptr, &mD3DBuffer);

        if (!err::HRCheck(hr)) {
            err::LogError("Unable to Create D3D Buffer: ", mName);
            return false;
        }
    }

    mIsBuilt = true;
    mByteWidth = byte_width;

    return true;
}


void D3DBuffer::MapData(void* data)
{
    if (!mIsBuilt) {
        err::LogError("Attempted to Map Unbuilt D3D Buffer");
        return;
    }

    D3D11_MAPPED_SUBRESOURCE mapped_buffer;
    HRESULT hr = D3D::GetInstance()->GetContext()->Map(mD3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

    if (!err::HRCheck(hr)) {
        err::LogError("Unable to Map D3D Buffer");
        return;
    }

    std::memcpy(mapped_buffer.pData, data, mByteWidth);
    D3D::GetInstance()->GetContext()->Unmap(mD3DBuffer, 0);
}

D3DBuffer::~D3DBuffer()
{
    SafeRelease(mD3DBuffer);
}


} // namespace TwilliEngine