#pragma once
#include "Resources/ResourceBase.hpp"


namespace TwilliEngine
{

class StructuredBuffer : public ResourceBase<StructuredBuffer>
{
public:
    StructuredBuffer() : mByteWidth(0),
                         mStructuredBuffer(nullptr),
                         mShaderResourceView(nullptr) {}
    
    StructuredBuffer(std::string_view name) : ResourceBase(name),
                                              mByteWidth(0), 
                                              mStructuredBuffer(nullptr),
                                              mShaderResourceView(nullptr) {}
 
    ~StructuredBuffer();

    bool Build(UINT byte_width, UINT num_elements);
    void MapData(void *data);

    ID3D11ShaderResourceView* const* GetShaderResourceView() { return &mShaderResourceView; }

private:
    UINT mByteWidth;
    ID3D11Buffer* mStructuredBuffer;
    ID3D11ShaderResourceView* mShaderResourceView;
};


} // namespace TwilliEngine

