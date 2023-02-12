#include "precompiled.hpp"
#include "D3DBuffer.hpp"

namespace TwilliEngine
{

D3DBuffer::~D3DBuffer()
{
    SafeRelease(mBuffer);
}

bool D3DBuffer::Build(UINT byte_width)
{
    D3D11_BUFFER_DESC desc;
    {
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.ByteWidth = byte_width;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.Usage = D3D11_USAGE_DYNAMIC;

        HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, nullptr, &mBuffer);

        if (err::HRCheck(hr)) {
            mIsBuilt = true;
            mByteWidth = byte_width;
        }
    }

    return mIsBuilt;
}

void D3DBuffer::MapData(void* data)
{
    if (!mIsBuilt) {
        err::LogError("Attempted to Map Unbuilt D3D Buffer");
        return;
    }

    D3D11_MAPPED_SUBRESOURCE mapped_buffer;
    HRESULT hr = D3D::GetInstance()->GetContext()->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

    if (!err::HRCheck(hr)) {
        err::LogError("Unable to Map D3D Buffer");
        return;
    }

    std::memcpy(mapped_buffer.pData, data, mByteWidth);
    D3D::GetInstance()->GetContext()->Unmap(mBuffer, 0);
}
} // namespace TwilliEngine