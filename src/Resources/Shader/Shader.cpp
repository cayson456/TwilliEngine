#include "precompiled.hpp"
#include "Shader.hpp"

#include <d3dcompiler.h>

namespace TwilliEngine
{
    // We know which buffers to assign based on the include on the top of the shader
void Shader::SearchAndAssignBuffers(const std::filesystem::path &filepath)
{
    std::ifstream in_file(filepath);
    std::stringstream str_stream;

    str_stream << in_file.rdbuf();
    std::string file_buffer = str_stream.str();

    size_t search_pos = 0;
    size_t search_end = 0;
    UINT buffer_id = 0;
    const std::string search = "#include \"../ConstantBuffers/";

    do
    {
        search_pos = file_buffer.find(search, search_end);
        if (search_pos == std::string::npos)
            break;

        search_pos += search.length();
        search_end = file_buffer.find('\"', search_pos);

        std::string buffer_name = file_buffer.substr(search_pos, search_end - search_pos);
        D3DBuffer::Key buffer = D3DBuffer::GetResourceWithName(buffer_name);

        AssignBuffer(buffer_id++, D3DBuffer::GetResourceWithName(buffer_name));
    } while (true);
}

void Shader::AssignBuffer(UINT slot, D3DBuffer::Key buffer)
{
    if (mAssignedBuffers[slot].IsValid()) {
        err::LogError("Warning, re-assigning already assigned buffer slot ", slot, " to: ", buffer->mName);
    }

    if (buffer.IsValid() && buffer->IsBuilt()) {
        mAssignedBuffers.insert_or_assign(slot, buffer);
    }
    else
        err::LogError("Attempted to assign a buffer that is invalid or unbuilt");
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
        err::LogError("Unable to compile shader - ", filepath, error_blob->GetBufferPointer());
        err::PrintLastWindowsError();

        SafeRelease(error_blob);
        SafeRelease(shader_blob);

        return hr;
    }

    *blob = shader_blob;
    return hr;
}

} // namespace TwilliEngine