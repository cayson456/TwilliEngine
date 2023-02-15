#pragma once
#include "Resources/ResourceBase.hpp"

namespace TwilliEngine
{
class Mesh : public ResourceBase<Mesh>
{
public:
    Mesh() : mIndexBuffer(nullptr), mBufferArray(), mHasVertexAttribute(), mNumIndices(0), mHasDeformer(false) {}
    Mesh(const std::string& name) : ResourceBase(name), mIndexBuffer(nullptr), mBufferArray(), mHasVertexAttribute(), mNumIndices(0), mHasDeformer(false) {}
    ~Mesh();
  
    void Build();
    void Bind();

    enum VertexAttributeType
    {
        Position,
        Normal,
        UV,
        Tangent,
        Binormal,
        COUNT
    };

    static constexpr UINT ATTRIBUTE_STRIDES[VertexAttributeType::COUNT]
        = {sizeof(float) * 3,
           sizeof(float) * 3,
           sizeof(float) * 3};

    // Does nothing if data is null
    template <typename T>
    void CreateVertexBuffer(VertexAttributeType type, const T *data, size_t num_elements);
    void CreateIndexBuffer(const UINT* indices, UINT num_indices);

    uint32_t mNumIndices;

    bool mHasDeformer;
    bool mHasVertexAttribute[VertexAttributeType::COUNT];
 
private:
    ID3D11Buffer *mIndexBuffer;
    ID3D11Buffer* mBufferArray[VertexAttributeType::COUNT];
};

template<typename T>
inline void Mesh::CreateVertexBuffer(VertexAttributeType type, const T *data, uint64_t num_elements)
{
    if (!data)
    return;

    D3D11_BUFFER_DESC desc;
    {
        desc.ByteWidth = static_cast<UINT>(num_elements) * ATTRIBUTE_STRIDES[type];
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.CPUAccessFlags = 0;
        desc.MiscFlags = 0;
        desc.StructureByteStride = ATTRIBUTE_STRIDES[type];
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    }

    D3D11_SUBRESOURCE_DATA res_data;
    {
        res_data.pSysMem = data;
        res_data.SysMemPitch = 0;
        res_data.SysMemSlicePitch = 0;
    }

    HRESULT hr = D3D::GetInstance()->GetDevice()->CreateBuffer(&desc, &res_data, &mBufferArray[type]);
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create vertex bufffer for mesh: ", mName);
        return;
    }

}

} // namespace TwilliEngine