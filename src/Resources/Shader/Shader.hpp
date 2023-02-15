#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"



namespace TwilliEngine
{
class Shader
{
public:
    Shader() {}
    ~Shader() {}

    virtual bool Build(const std::filesystem::path& filepath) = 0;
    virtual void Bind() = 0;

    void AssignBuffer(UINT slot, D3DBuffer::Key buffer);

    enum Type
    {
        Vertex,
        Pixel,
        Compute,
        COUNT
    };

protected:
    void SearchAndAssignBuffers(const std::filesystem::path& filepath);
    

    HRESULT CompileShader(const std::filesystem::path& filepath, LPCSTR profile, ID3DBlob** blob);

    std::map<UINT, D3DBuffer::Key> mAssignedBuffers;
};



} // namespace TwilliEngine