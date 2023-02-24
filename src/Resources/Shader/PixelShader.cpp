#include "precompiled.hpp"
#include "PixelShader.hpp"

namespace TwilliEngine
{

PixelShader::~PixelShader()
{
    SafeRelease(mPixelShader);
}

bool PixelShader::Build(const std::filesystem::path& filepath)
{
    ID3DBlob* shader_blob = nullptr;
    
    HRESULT hr = CompileShader(filepath, "ps_5_0", &shader_blob);
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create pixel shader: ", filepath);
        err::PrintLastWindowsError();
        SafeRelease(shader_blob);
        return false;
    }

    hr = D3D::GetInstance()->GetDevice()->CreatePixelShader(shader_blob->GetBufferPointer(),
                                                                        shader_blob->GetBufferSize(), 
                                                                    NULL, &mPixelShader);
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create pixel shader: ", filepath);
        err::PrintLastWindowsError();
        SafeRelease(shader_blob);
        return false;
    }
    
    SafeRelease(shader_blob);
    SearchAndAssignBuffers(filepath);

    return mIsBuilt = true;
}

void PixelShader::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind unbuilt pixel shader: ", mName);
        return;
    }

    D3D::GetInstance()->GetContext()->PSSetShader(mPixelShader, NULL, 0);

    for (auto &it : mAssignedConstantBuffers) {
        D3D::GetInstance()->GetContext()->PSSetConstantBuffers(it.first, 1, it.second->GetBuffer());
    }
    for (auto& it : mAssignedStructuredBuffers) {
        D3D::GetInstance()->GetContext()->PSSetShaderResources(it.first, 1, it.second->GetShaderResourceView());
    }
}

/*
ResourceID PixelShader::Create()
{
    ResourceID resource_id;
    resource_id.GenerateNewID();

    sResources.emplace(resource_id, std::make_unique<PixelShader>());
    return resource_id;
}
*/
} // namespace TwilliEngine