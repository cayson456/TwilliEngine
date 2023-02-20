#pragma once
#include "Resources/ResourceBase.hpp"
#include "BufferDefinitions.hpp"

namespace TwilliEngine
{

class D3DBuffer : public ResourceBase<D3DBuffer>
{
public:
    D3DBuffer() : mByteWidth(0), 
                  mD3DBuffer(nullptr), 
                  mBuffer(nullptr) {}
    
    D3DBuffer(std::string_view name) : ResourceBase(name), 
                                       mByteWidth(0), 
                                       mD3DBuffer(nullptr), 
                                       mBuffer(nullptr) {}
    ~D3DBuffer();

    template <typename T>
    bool Build();

    template <typename T>
    T* GetBuffer();

    template <typename T>
    void MapDataToBuffer(const T& data);

    ID3D11Buffer* const* GetD3DBuffer() { return &mD3DBuffer; }

private:
    UINT mByteWidth;
    ID3D11Buffer* mD3DBuffer;
};

// Do I wanna have the buffer struct on the D3DBuffer class, or on the related component?

// If i have it on the D3DBuffer class
// - I'd have the components calculate the data to put in the struct buffer each frame

/////////////////////////////////////////////////////////
// If I have it on the related ccomponent
// - I'd recalculate the data only when needed, but each instance of the component would need it's own 
//   struct buffer to be mapped onto the internal D3DBuffer.
//////////////////////////////////////////////

// When draw time comes, the shaders will know which buffers to assign
} // namespace TwilliEngine

#include "D3DBuffer.inl"