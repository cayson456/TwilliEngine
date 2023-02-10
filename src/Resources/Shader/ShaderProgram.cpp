#include "precompiled.hpp"
#include "ShaderProgram.hpp"



namespace TwilliEngine
{
ShaderProgram::ShaderProgram()
{
}
ShaderProgram::~ShaderProgram()
{
}
void ShaderProgram::Build()
{
}
void ShaderProgram::AttachShader(Shader::Type type, Shader::Key shader)
{
    if (shader.IsValid()) {
        err::AssertWarn(!mShaders[type].IsValid(), "Warning! Replaced an already attached shader with a new one!");
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