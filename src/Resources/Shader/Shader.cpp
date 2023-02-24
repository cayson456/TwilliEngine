#include "precompiled.hpp"
#include "Shader.hpp"

#include <d3dcompiler.h>

namespace TwilliEngine
{
    // We know which buffers to assign based on the the macros used in the .hlsl file
    // _c_ denotes constant buffer
    // _t_ denotes texture slot
void Shader::SearchAndAssignBuffers(const std::filesystem::path &filepath)
{
    std::ifstream in_file(filepath);
    std::stringstream str_stream;

    str_stream << in_file.rdbuf();
    std::string file_buffer = str_stream.str();

    size_t search_pos = 0; 
    const std::string search_constant_buffer = "_c_";
    do
    {
        search_pos = file_buffer.find(search_constant_buffer, search_pos);
        if (search_pos == std::string::npos)
            break;

        search_pos += search_constant_buffer.length();
        size_t search_end = file_buffer.find('(', search_pos);
        size_t search_end_2 = file_buffer.find(')', search_end);

        std::string name = file_buffer.substr(search_pos, search_end - search_pos);
        std::string slot = file_buffer.substr(search_end+1, search_end_2 - search_end-1);

        AssignConstantBuffer(std::stoi(slot), D3DBuffer::GetResourceWithName(name));
    } while (true);

    search_pos = 0;
    const std::string search_structured_buffer = "_t_";

    do
    {
        search_pos = file_buffer.find(search_structured_buffer, search_pos);
        if (search_pos == std::string::npos)
            break;

        search_pos += search_constant_buffer.length();
        size_t search_end = file_buffer.find('(', search_pos);
        size_t search_end_2 = file_buffer.find(')', search_end);

        std::string name = file_buffer.substr(search_pos, search_end - search_pos);
        std::string slot = file_buffer.substr(search_end+1, search_end_2 - search_end -1);

        AssignStructuredBuffer(std::stoi(slot), StructuredBuffer::GetResourceWithName(name));
    } while (true);
}

void Shader::AssignConstantBuffer(UINT slot, D3DBuffer::Key buffer)
{
    if (mAssignedConstantBuffers[slot].IsValid()) {
        err::LogError("Warning, re-assigning already assigned constant buffer slot ", slot, " to: ", buffer->mName);
    }

    if (buffer.IsValid() && buffer->IsBuilt()) {
        mAssignedConstantBuffers.insert_or_assign(slot, buffer);
    }
    else
        err::LogError("Attempted to assign a constant buffer that is invalid or unbuilt");
}

void Shader::AssignStructuredBuffer(UINT slot, StructuredBuffer::Key buffer)
{
    if (mAssignedStructuredBuffers[slot].IsValid()) {
        err::LogError("Warning, re-assigning already assigned structured buffer slot ", slot, " to: ", buffer->mName);
    }

    if (buffer.IsValid() && buffer->IsBuilt()) {
        mAssignedStructuredBuffers.insert_or_assign(slot, buffer);
    }
    else
        err::LogError("Attempted to assign a structured buffer that is invalid or unbuilt");
}

HRESULT Shader::CompileShader(const std::filesystem::path& filepath, LPCSTR profile, ID3DBlob** blob)
{
    if (filepath.empty() || !profile || !blob)
        return E_INVALIDARG;

    *blob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* shader_blob = nullptr;
    ID3DBlob* error_blob = nullptr;

    HRESULT hr = D3DCompileFromFile(filepath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                    "main", profile, flags, 0, &shader_blob, &error_blob);

    if (!err::HRCheck(hr))
    {
        err::LogError("Unable to compile shader - ", filepath);
        OutputDebugStringA((char*)(error_blob->GetBufferPointer()));
        err::PrintLastWindowsError();

        SafeRelease(error_blob);
        SafeRelease(shader_blob);

        return hr;
    }

    *blob = shader_blob;
    return hr;
}

} // namespace TwilliEngine