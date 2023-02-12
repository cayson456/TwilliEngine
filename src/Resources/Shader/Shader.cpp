#include "precompiled.hpp"
#include "Shader.hpp"

#include <d3dcompiler.h>

namespace TwilliEngine
{

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