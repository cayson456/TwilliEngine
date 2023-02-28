#include "precompiled.hpp"
#include "GeometryShader.hpp"

#include <d3dcompiler.h>

namespace TwilliEngine
{

GeometryShader::~GeometryShader()
{
    SafeRelease(mGeometryShader);
}

bool GeometryShader::Build(const std::filesystem::path& filepath)
{
    // Compile vertex shader
    /////////////////////////////////////////////////////
    ID3DBlob* shader_blob = nullptr;

    HRESULT hr = CompileShader(filepath, "gs_5_0", &shader_blob);
    if (!err::HRCheck(hr))
        return false;

    hr = D3D::GetInstance()->GetDevice()->CreateGeometryShader(shader_blob->GetBufferPointer(),
                                                               shader_blob->GetBufferSize(), 
                                                               NULL, &mGeometryShader);
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create geometry shader: ", filepath);
        err::PrintLastWindowsError();
        SafeRelease(shader_blob);
        return false;
    }

    SafeRelease(shader_blob);
    SearchAndAssignBuffers(filepath);

    return mIsBuilt = true;
}

void GeometryShader::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind unbuilt geometry shader: ", mName);
        return;
    }

    D3D::GetInstance()->GetContext()->GSSetShader(mGeometryShader, NULL, 0);

    for (auto& it : mAssignedConstantBuffers) {
        D3D::GetInstance()->GetContext()->GSSetConstantBuffers(it.first, 1, it.second->GetBuffer());
    }
    for (auto& it : mAssignedStructuredBuffers) {
        D3D::GetInstance()->GetContext()->GSSetShaderResources(it.first, 1, it.second->GetShaderResourceView());
    }
}

}