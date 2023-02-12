#include "precompiled.hpp"
#include "PixelShader.hpp"

namespace TwilliEngine
{

PixelShader::~PixelShader()
{
    SafeRelease(mPixelShader);
}

void PixelShader::Build(const std::filesystem::path& filepath)
{
    ID3DBlob* shader_blob = nullptr;

    if (err::HRCheck(CompileShader(filepath, "ps_5_0", &shader_blob))) {
        HRESULT hr = D3D::GetInstance()->GetDevice()->CreatePixelShader(shader_blob->GetBufferPointer(),
                                                                        shader_blob->GetBufferSize(), 
                                                                        NULL, &mPixelShader);
        if (!err::HRCheck(hr)) {
            err::LogError("Unable to create pixel shader: ", filepath);
            err::PrintLastWindowsError();
            SafeRelease(shader_blob);
        }
    }
    else 
        return;

    SafeRelease(shader_blob);
    
    if (mPixelShader)
        mIsBuilt = true;
}

void PixelShader::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind unbuilt pixel shader: ", mName);
        return;
    }

    D3D::GetInstance()->GetContext()->PSSetShader(mPixelShader, NULL, 0);

    for (auto &it : mAssignedBuffers) {
        D3D::GetInstance()->GetContext()->PSSetConstantBuffers(it.first, 1, it.second->GetBuffer());
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