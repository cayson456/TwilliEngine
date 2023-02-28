#include "precompiled.hpp"
#include "StructuredBuffer.hpp"

namespace TwilliEngine
{
bool StructuredBuffer::Build(UINT byte_width, UINT num_elements)
{
    if (mIsBuilt) {
        err::LogError("Attempted to build already built structured buffer ", mName);
        return false;
    }

    {
        D3D11_BUFFER_DESC desc;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.ByteWidth = byte_width * num_elements;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        desc.StructureByteStride = byte_width;
        desc.Usage = D3D11_USAGE_DYNAMIC;

        HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, nullptr, &mStructuredBuffer);

        if (!err::HRCheck(hr)) {
            err::LogError("Unable to Create Structured Buffer Buffer: ", mName);
            return false;
        }
    }

    {
        D3D11_SHADER_RESOURCE_VIEW_DESC desc;
        desc.Format = DXGI_FORMAT_UNKNOWN;
        desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        desc.Buffer.FirstElement = 0;
        desc.Buffer.NumElements = num_elements;

        HRESULT hr = D3D::GetInstance()->GetDevice()->CreateShaderResourceView(mStructuredBuffer, &desc, &mShaderResourceView);

        if (!err::HRCheck(hr)) {
            err::LogError("Unable to Create Shader Resource View for Structured Buffer: ", mName);
            return false;
        }
    }

    mByteWidth = byte_width * num_elements;
    mIsBuilt = true;
    return true;
}


void StructuredBuffer::MapData(void* data)
{
    if (!mIsBuilt) {
        err::LogError("Attempted to Map Unbuilt Structured Buffer");
        return;
    }

    D3D11_MAPPED_SUBRESOURCE mapped_buffer;
    HRESULT hr = D3D::GetInstance()->GetContext()->Map(mStructuredBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_buffer);

    if (!err::HRCheck(hr)) {
        err::LogError("Unable to Map Structured Buffer");
        return;
    }

    std::memcpy(mapped_buffer.pData, data, mByteWidth);
    D3D::GetInstance()->GetContext()->Unmap(mStructuredBuffer, 0);
}

StructuredBuffer::~StructuredBuffer()
{
    SafeRelease(mStructuredBuffer);
    SafeRelease(mShaderResourceView);
}


} // namespace TwilliEngine