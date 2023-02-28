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
    else
        D3D::GetInstance()->GetContext()->VSSetShader(nullptr, nullptr, 0);

    if (mGeometryShader)
        mGeometryShader->Bind();
    else
        D3D::GetInstance()->GetContext()->GSSetShader(nullptr, nullptr, 0);

    if (mPixelShader)
        mPixelShader->Bind();
    else
        D3D::GetInstance()->GetContext()->PSSetShader(nullptr, nullptr, 0);

    if (mComputeShader)
        mComputeShader->Bind();
    else
        D3D::GetInstance()->GetContext()->CSSetShader(nullptr, nullptr, 0);
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

void ShaderProgram::AttachGeometryShader(GeometryShader::Key geometry_shader)
{
    if (mGeometryShader)
        err::LogError("Warning: Replacing Geometry Shader in ", mName);

    if (geometry_shader.IsValid() && geometry_shader->IsBuilt()) {
        mGeometryShader = geometry_shader;
    }
    else
        err::LogError("Attempted to attach unbuilt or invalid geometry shader in ", mName);
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