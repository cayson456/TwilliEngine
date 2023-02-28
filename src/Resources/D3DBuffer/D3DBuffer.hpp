#pragma once
#include "Resources/ResourceBase.hpp"
#include "ConstantBufferDefinitions.hpp"

namespace TwilliEngine
{

class D3DBuffer : public ResourceBase<D3DBuffer>
{
public:
    D3DBuffer() : mByteWidth(0), 
                  mD3DBuffer(nullptr) {}
    
    D3DBuffer(std::string_view name) : ResourceBase(name), 
                                       mByteWidth(0), 
                                       mD3DBuffer(nullptr) {}
    ~D3DBuffer();

    bool Build(UINT byte_width);
    void MapData(void *data);

    ID3D11Buffer* const* GetBuffer() { return &mD3DBuffer; }

private:
    UINT mByteWidth;
    ID3D11Buffer* mD3DBuffer;
};

// Do I wanna have the buffer struct on the D3DBuffer class, or on the related component?

// If i have it on the D3DBuffer class
// - I'd have the components calculate the data to put in the struct buffer each frame

/////////////////////////////////////////////////////////
// If I have it on the related component
// - I'd recalculate the data only when needed, but each instance of the component would need it's own 
//   struct buffer to be mapped onto the internal D3DBuffer.
//////////////////////////////////////////////

// When draw time comes, the shaders will know which D3DBuffer class to map data on
// and will also know which components to pull data from (how?)

// We know the D3DBuffer classes assigned to each shader because it pulls the name
// from the #includes in the .hlsl file
// Can we figure out how...


// Maybe I should see how Unity does shaders


} // namespace TwilliEngine

#include "D3DBuffer.inl"