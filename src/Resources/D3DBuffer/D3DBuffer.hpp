#pragma once
#include "Resources/ResourceBase.hpp"

namespace TwilliEngine
{
class D3DBuffer : public ResourceBase<D3DBuffer>
{
public:
    D3DBuffer() : mByteWidth(0), mBuffer(nullptr) {}
    D3DBuffer(std::string_view name) : ResourceBase(name), mByteWidth(0), mBuffer(nullptr) {}
    ~D3DBuffer();

    bool Build(UINT byte_width);

    void MapData(void* data);

    ID3D11Buffer* const* GetBuffer() { return &mBuffer; }

private:
    UINT mByteWidth;
    ID3D11Buffer* mBuffer;
};

} // namespace TwilliEngine