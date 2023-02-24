#include "precompiled.hpp"
#include "ShaderProgram.hpp"



namespace TwilliEngine
{

bool ShaderProgram::Build()
{
    bool valid_vertex = mVertexShader.IsValid() && mVertexShader->IsBuilt();
    bool valid_pixel = mPixelShader.IsValid() && mPixelShader->IsBuilt();
    bool valid_compute = mComputeShader.IsValid() && mComputeShader->IsBuilt();

    if ((valid_vertex && valid_pixel) || valid_compute)
        mIsBuilt = true;
    
    return mIsBuilt;
}

void ShaderProgram::Bind()
{
    if (!mIsBuilt) {
        err::LogError("Attempted to bind unbuilt shader program: ", mName);
        return;
    }
    
    if (mVertexShader)
        mVertexShader->Bind();
    if (mPixelShader)
        mPixelShader->Bind();
    if (mComputeShader)
        mComputeShader->Bind();
}

void ShaderProgram::AttachVertexShader(VertexShader::Key vertex_shader)
{
    if (mVertexShader)
        err::LogError("Warning: Replacing Vertex Shader in ", mName);

    if (vertex_shader.IsValid() && vertex_shader->IsBuilt()) {
        mVertexShader = vertex_shader;
    }
    else
        err::LogError("Attempted to attach unbuilt or invalid vertex shader in ", mName);
}

void ShaderProgram::AttachPixelShader(PixelShader::Key pixel_shader)
{
    if (mPixelShader)
        err::LogError("Warning: Replacing Pixel Shader in ", mName);

    if (pixel_shader.IsValid() && pixel_shader->IsBuilt()) {
        mPixelShader = pixel_shader;
    }
    else
        err::LogError("Attempted to attach unbuilt or invalid pixel shader in ", mName);
}

void ShaderProgram::AttachComputeShader(ComputeShader::Key compute_shader)
{
    if (mComputeShader)
        err::LogError("Warning: Replacing Compute Shader in ", mName);

    if (compute_shader.IsValid() && compute_shader->IsBuilt()) {
        mComputeShader = compute_shader;
    }
    else
        err::LogError("Attempted to attach unbuilt or invalid compute shader in ", mName);
}
} 