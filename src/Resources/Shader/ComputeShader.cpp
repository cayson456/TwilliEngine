#include "precompiled.hpp"
#include "ComputeShader.hpp"

namespace TwilliEngine
{

ComputeShader::~ComputeShader()
{
    SafeRelease(mComputeShader);
}

bool ComputeShader::Build(const std::filesystem::path& filepath)
{
    // Compile vertex shader
    /////////////////////////////////////////////////////
    ID3DBlob* shader_blob = nullptr;

    HRESULT hr = CompileShader(filepath, "cs_5_0", &shader_blob);
    if (!err::HRCheck(hr))
        return false;

    hr = D3D::GetInstance()->GetDevice()->CreateComputeShader(shader_blob->GetBufferPointer(),
                                                                          shader_blob->GetBufferSize(), 
                                                                          NULL, &mComputeShader);
    if (!err::HRCheck(hr)) {
        err::LogError("Unable to create compute shader: ", filepath);
        err::PrintLastWindowsError();
        SafeRelease(shader_blob);
        return false;
    }

    SafeRelease(shader_blob);
    SearchAndAssignBuffers(filepath);

    return mIsBuilt = true;
}

void ComputeShader::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind unbuilt compute shader: ", mName);
        return;
    }

    D3D::GetInstance()->GetContext()->CSSetShader(mComputeShader, NULL, 0);

    for (auto& it : mAssignedBuffers) {
        D3D::GetInstance()->GetContext()->CSSetConstantBuffers(it.first, 1, it.second->GetBuffer());
    }
}

/*
ResourceID ComputeShader::Create()
{
  ResourceID resource_id;
  resource_id.GenerateNewID();

  sResources.emplace(resource_id, std::make_unique<ComputeShader>());
  return resource_id;
}
*/

} // namespace TwilliEngine