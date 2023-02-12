#include "precompiled.hpp"
#include "Mesh.hpp"

namespace TwilliEngine
{

Mesh::~Mesh()
{
    SafeRelease(mIndexBuffer);

    for (size_t i = 0; i < VertexAttributeType::COUNT; ++i)
        SafeRelease(mBufferArray[i]);
}

void Mesh::Build()
{
    if (mIsBuilt) {
        err::LogError("Warning: Attempted to build an already built mesh");
        return;
    }

    mIsBuilt = true;
}

void Mesh::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind an unbuilt mesh!");
        return;
    }

    UINT slot = 0;

    for (UINT i = 0; i < VertexAttributeType::COUNT; ++i)
    {
        UINT offset = 0;
        if (mBufferArray[i])
            D3D::GetInstance()->GetContext()->IASetVertexBuffers(slot++, 1, &mBufferArray[i], &ATTRIBUTE_STRIDES[i], &offset);
    }

    D3D::GetInstance()->GetContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void Mesh::CreateIndexBuffer(const UINT *indices, UINT num_indices)
{
    D3D11_BUFFER_DESC desc;
    {
        desc.ByteWidth = static_cast<UINT>(sizeof(UINT) * num_indices);
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = sizeof(unsigned int);
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    }

    D3D11_SUBRESOURCE_DATA res_data;
    {
        res_data.pSysMem = indices;
        res_data.SysMemPitch = 0;
        res_data.SysMemSlicePitch = 0;
    }

    HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, &res_data, &mIndexBuffer);
    
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create index bufffer for mesh: ", mName);
        return;
    }

    mNumIndices = num_indices;
}

}
