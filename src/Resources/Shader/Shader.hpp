#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"



namespace TwilliEngine
{
class Shader : public ResourceBase<Shader>
{
public:
    Shader() {}
    Shader(const std::string &name) : ResourceBase(name) {}
    ~Shader() {}

    virtual void Build(const std::filesystem::path& filepath) = 0;
    virtual void Bind() = 0;

    enum Type
    {
        Vertex,
        Pixel,
        Compute,
        COUNT
    };

protected:
    HRESULT CompileShader(const std::filesystem::path& filepath, LPCSTR profile, ID3DBlob** blob);

    std::map<UINT, D3DBuffer::Key> mAssignedBuffers;
};



} // namespace TwilliEngine