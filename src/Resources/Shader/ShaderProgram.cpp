#include "precompiled.hpp"
#include "ShaderProgram.hpp"



namespace TwilliEngine
{

void ShaderProgram::Build()
{
}
void ShaderProgram::AttachShader(Shader::Type type, Shader::Key shader)
{
    if (shader.IsValid()) {
        err::LogError("Warning! Replaced an already attached shader with a new one!");
        mShaders[type] = shader;
    }
}

void ShaderProgram::Bind()
{
    for (auto &shader : mShaders) {
        if (shader.IsValid())
            shader->Bind();
    }
}
} 