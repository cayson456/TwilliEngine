#pragma once
#include "Resources/ResourceBase.hpp"
#include "Resources/Model/Mesh.hpp"
#include "Resources/D3DBuffer/D3DBuffer.hpp"
#include "Resources/StructuredBuffer/StructuredBuffer.hpp"


namespace TwilliEngine
{
class Shader
{
public:
    Shader() {}
    ~Shader() {}

    virtual bool Build(const std::filesystem::path& filepath) = 0;
    virtual void Bind() = 0;

    void AssignConstantBuffer(UINT slot, D3DBuffer::Key buffer);
    void AssignStructuredBuffer(UINT slot, StructuredBuffer::Key buffer);

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

    std::map<UINT, D3DBuffer::Key> mAssignedConstantBuffers;
    std::map<UINT, StructuredBuffer::Key> mAssignedStructuredBuffers;
};



} // namespace TwilliEngine