#pragma once
#include "Resources/ResourceBase.hpp"

#include "Resources/Shader/Shader.hpp"
#include "Resources/Shader/VertexShader.hpp"
#include "Resources/Shader/PixelShader.hpp"
#include "Resources/Shader/ComputeShader.hpp"
namespace TwilliEngine
{

class ShaderProgram : public ResourceBase<ShaderProgram>
{
public:
    ShaderProgram() {}
    ShaderProgram(std::string_view name) : ResourceBase(name) {}
    ~ShaderProgram() {}
  
    bool Build();
    void Bind();

    // TODO:
    void SetConstantBuffers() {}
    // TODO:
    void SetRenderTargetView() {}

    void AttachVertexShader(VertexShader::Key vertex_shader);
    void AttachPixelShader(PixelShader::Key pixel_shader);
    void AttachComputeShader(ComputeShader::Key compute_shader);

    VertexShader::Key GetVertexShader() { return mVertexShader; }
    PixelShader::Key GetPixelShader() { return mPixelShader; }
    ComputeShader::Key GetComputeShader() { return mComputeShader; }

private:
    VertexShader::Key mVertexShader;
    PixelShader::Key mPixelShader;
    ComputeShader::Key mComputeShader;
};

}